#include "pch.hpp"
#include "ECS/ECS_impl.hpp"
#include "AssetsStorage.hpp"
#include "OpenGL/OpenGl.hpp"
#include "Assets.hpp"

Flicker::Handle Flicker::AssetsStorage::addShader(const std::string& shaderName)
{
    auto sources = Flicker::load_shader(shaderName);
    auto& storage = getStorage<Flicker::Shader>();
    storage.emplace_back(Flicker::OpenGL::create_shader(sources));
    return storage.size() - 1;
}

Flicker::Handle Flicker::AssetsStorage::createMaterial(Flicker::Handle shaderHandle)
{
    auto& storage = getStorage<Flicker::Material>();
    storage.emplace_back(getAsset<Flicker::Shader>(shaderHandle));
    return storage.size() - 1;
}

Flicker::Handle Flicker::AssetsStorage::createMesh(const std::vector<Flicker::Vertex>& vertices, const std::vector<size_t>& indices)
{
    auto& storage = getStorage<Flicker::Mesh>();
    storage.emplace_back(Flicker::OpenGL::createMesh(vertices, indices));
    return storage.size() - 1;
}