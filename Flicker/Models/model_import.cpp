#include "model_import.hpp"
#include "Model.hpp"
#include "Mesh.hpp"
#include "Material/LitMaterial.hpp"
#include "Texture/Texture.hpp"
#include "Assets/Assets.hpp"

glm::vec3 vec3 (aiVector3D vec)
{
    return {vec.x, vec.y, vec.z}; 
}

glm::vec2 vec2 (aiVector3D vec)
{
    return {vec.x, vec.y};
}

void parse_mesh(const aiMesh* mesh, const aiScene* scene, std::vector<Flicker::Mesh>& meshes, std::vector<std::shared_ptr<Flicker::Material>>& materials, const std::string& modelFolder)
{
    std::vector<Flicker::Vertex> verts;
    std::vector<int> indices;

    for(size_t i = 0; i < mesh->mNumVertices; i++)
    {
        aiVector3D position = mesh->mVertices[i];
        aiVector3D normal = mesh->mNormals[i];

        Flicker::Vertex v;
        v.position = vec3(position);
        v.normal = vec3(normal);

        v.uv = mesh->mTextureCoords[0]
            ? vec2(mesh->mTextureCoords[0][i])
            : glm::vec2();

        verts.push_back(v);
    }

    for(size_t i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for(size_t j = 0; j < face.mNumIndices; ++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    std::shared_ptr<Flicker::LitMaterial> m = std::make_shared<Flicker::LitMaterial>(); 

    glm::vec4 diffuse, specular;
    float shininess;
    if (material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse) == AI_SUCCESS)
    {
        m->setDiffuseColor(diffuse);
    }

    if (material->Get(AI_MATKEY_COLOR_SPECULAR, specular) == AI_SUCCESS)
    {
        m->setSpecularColor(specular);
    }

    if (material->Get(AI_MATKEY_SHININESS, shininess))
    {
        m->setShininess(shininess);
    }

    if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) 
    {
        aiString path;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
        
        std::shared_ptr<Flicker::Texture> diffuse = Flicker::Assets::loadTextureByPath(modelFolder + '/' + path.C_Str());
        m->setDiffuseTexture(diffuse.get());
    }

    if (material->GetTextureCount(aiTextureType_SPECULAR) > 0)
    {
        aiString path;
        material->GetTexture(aiTextureType_SPECULAR, 0, &path);
        
        std::shared_ptr<Flicker::Texture> specular = Flicker::Assets::loadTextureByPath(modelFolder + '/' + path.C_Str());
        m->setSpecularTexture(specular.get());
    }

    meshes.emplace_back(verts, indices);
    materials.push_back(m);
}

void parse_node(const aiNode* node, const aiScene* scene, Flicker::Node* parent, glm::mat4& transform, const std::string& modelFolder)
{
    if (node->mNumMeshes > 0)
    {
        std::vector<Flicker::Mesh> meshes;
        std::vector<std::shared_ptr<Flicker::Material>> materials;
        for (size_t i = 0; i < node->mNumMeshes; i++)
        {
            parse_mesh(scene->mMeshes[node->mMeshes[i]], scene, meshes, materials, modelFolder);
        }
        
        Flicker::Model* model = new Flicker::Model(meshes, materials);
        model->setTRS(transform);
        model->setParent(parent);
        parent = model;
        transform = glm::mat4(1.f);
    }
    else
    {
        transform = *reinterpret_cast<const glm::mat4*>(&node->mTransformation) * transform;
    }

    for(size_t i = 0; i < node->mNumChildren; ++i)
    {
        parse_node(node->mChildren[i], scene, parent, transform, modelFolder);
    }
}

std::shared_ptr<Flicker::Node> Flicker::parse_scene(const aiScene* scene, const std::string& filePath)
{
    std::shared_ptr<Node> rootNode = std::make_shared<Node>();

    int index = filePath.find_last_of("/\\");
    parse_node(scene->mRootNode, scene, rootNode.get(), glm::mat4(1.f), filePath.substr(0, index));

    return rootNode;
}