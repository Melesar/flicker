#pragma once
#include "pch.hpp"
#include "ECS/ECS_impl.hpp"
#include "AssetsStorage.hpp"
#include "assimp_parse.hpp"
#include "OpenGL/OpenGl.hpp"

void parse_meshes(const aiScene* scene, Flicker::AssetsStorage& assetsStorage);
void parse_materials(const aiScene* scene, Flicker::AssetsStorage& assetsStorage);
void parse_hierarchy(const aiScene* scene, const Flicker::AssetsStorage& assetsStorage, Flicker::EntityManager& entityManager);
void parse_node(const aiNode* node, const aiScene* scene, Flicker::Handle& parent, glm::mat4& transform, const Flicker::AssetsStorage& assetsStorage, Flicker::EntityManager& entityManager);

void Flicker::AssimpAPI::parse(const aiScene* scene, Flicker::EntityManager& entityManager, Flicker::AssetsStorage& assetsStorage)
{
    parse_meshes(scene, assetsStorage);
    parse_materials(scene, assetsStorage);
    parse_hierarchy(scene, assetsStorage, entityManager);
}

void parse_meshes(const aiScene* scene, Flicker::AssetsStorage& assetsStorage)
{
    for (size_t meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
    {
        aiMesh* mesh = scene->mMeshes[meshIndex];
        glm::vec3* vertices = reinterpret_cast<glm::vec3*>(mesh->mVertices);
        glm::vec3* normals = reinterpret_cast<glm::vec3*>(mesh->mNormals);
        glm::vec2* uvs = reinterpret_cast<glm::vec2*>(mesh->mTextureCoords[0]);

        std::vector<Flicker::Vertex> verticesVector;
        verticesVector.reserve(mesh->mNumVertices);
        for (size_t vertIndex = 0; vertIndex < mesh->mNumVertices; vertIndex++)
        {
            verticesVector.emplace_back(vertices[vertIndex], normals[vertIndex], uvs[vertIndex]);
        }
        
        std::vector<size_t> indicesVector;
        for (size_t faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++)
        {
            aiFace face = mesh->mFaces[faceIndex];
            for (size_t trisIndex = 0; trisIndex < face.mNumIndices; trisIndex++)
            {
                indicesVector.push_back(face.mIndices[trisIndex]);
            }
        }
        
        assetsStorage.createMesh(verticesVector, indicesVector);
    }
}

void parse_materials(const aiScene* scene, Flicker::AssetsStorage& assetsStorage)
{
    const Flicker::Shader& litShader = assetsStorage.getAsset<Flicker::Shader>(Flicker::LIT_SHADER_HANDLE);
    GLint diffusePropId = Flicker::OpenGL::get_shader_property_id(litShader, "material.diffuseColor");
    GLint specularPropId = Flicker::OpenGL::get_shader_property_id(litShader, "material.specularColor");
    GLint shininessPropId = Flicker::OpenGL::get_shader_property_id(litShader, "material.shininess");
    for (size_t materialIndex = 0; materialIndex < scene->mNumMaterials; materialIndex++)
    {
        aiMaterial* parsedMaterial = scene->mMaterials[materialIndex];
        Flicker::Handle materialHandle = assetsStorage.createMaterial(Flicker::LIT_SHADER_HANDLE);
        Flicker::Material& material = assetsStorage.getAsset<Flicker::Material>(materialHandle);

        glm::vec4 diffuse, specular;
        float shininess;
        if (parsedMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse) == AI_SUCCESS)
        {
            material.Vec4Params[diffusePropId] = diffuse;
        }

        if (parsedMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specular) == AI_SUCCESS)
        {
            material.Vec4Params[specularPropId] = specular;
        }

        if (parsedMaterial->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS)
        {
            material.FloatParams[shininessPropId] = shininess;
        }
    }
    
}

void parse_hierarchy(const aiScene* scene, const Flicker::AssetsStorage& assetsStorage, Flicker::EntityManager& entityManager)
{
    glm::mat4 transform (1.f);
    Flicker::Handle parent {10000};
    parse_node(scene->mRootNode, scene, parent, transform, assetsStorage, entityManager);
    entityManager.refresh();
}

void parse_node(const aiNode* node, const aiScene* scene, Flicker::Handle& parent, glm::mat4& transform, const Flicker::AssetsStorage& assetsStorage, Flicker::EntityManager& entityManager)
{
    if (node->mNumMeshes > 0)
    {
        for (size_t i = 0; i < node->mNumMeshes; i++)
        {
            size_t meshIndex = node->mMeshes[i];
            size_t materialIndex = scene->mMeshes[meshIndex]->mMaterialIndex;
            ecs::EntityHandle entity = entityManager.createEntity();
            entityManager.addComponent(entity, Flicker::MeshInstanceComponent {meshIndex, materialIndex});
            entityManager.addComponent(entity, Flicker::TransformComponent {parent.Index, transform});
            parent.Index = *entity;
        }

        transform = glm::mat4(1.f);
    }
    else
    {
        transform = *reinterpret_cast<const glm::mat4*>(&node->mTransformation) * transform;
    }

    for (size_t i = 0; i < node->mNumChildren; i++)
    {
        parse_node(node->mChildren[i], scene, parent, transform, assetsStorage, entityManager);
    }
    
    
}