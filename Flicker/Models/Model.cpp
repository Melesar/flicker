#include <assimp/scene.h>
#include "Model.hpp"
#include "Mesh.hpp"

glm::vec3 vec3 (aiVector3D vec)
{
    return {vec.x, vec.y, vec.z}; 
}

glm::vec2 vec2 (aiVector3D vec)
{
    return {vec.x, vec.y};
}

Flicker::Model::Model(const aiScene* scene)
{
    processNode(scene->mRootNode, scene);
}

Flicker::Model::~Model()
{

}

size_t Flicker::Model::meshesCount() const
{
    return m_Meshes.size();
}

const Flicker::Mesh& Flicker::Model::getMesh(size_t index) const
{
    assert(index < m_Meshes.size());

    return m_Meshes[index];
}


void Flicker::Model::processNode(aiNode* node, const aiScene* scene)
{
    for(size_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene);
    }

    for(size_t i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}



void Flicker::Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Flicker::Vertex> verts;
    std::vector<int> indices;

    for(size_t i = 0; i < mesh->mNumVertices; i++)
    {
        aiVector3D position = mesh->mVertices[i];
        aiVector3D normal = mesh->mNormals[i];
        

        Vertex v;
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

    m_Meshes.emplace_back(verts, indices);
}
