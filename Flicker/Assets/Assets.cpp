#include "Assets.hpp"
#include "Shader/Shader.hpp"
#include "Texture/Texture.hpp"
#include "Scene/Node.hpp"
#include "Models/model_import.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::unordered_map<std::string, std::shared_ptr<Flicker::Shader>> Flicker::Assets::m_LoadedShaders;
std::unordered_map<std::string, std::shared_ptr<Flicker::Node>> Flicker::Assets::m_LoadedModels;
std::unordered_map<std::string, std::shared_ptr<Flicker::Texture>> Flicker::Assets::m_LoadedTextures;

std::shared_ptr<Flicker::Shader> Flicker::Assets::loadShader(std::string name)
{
    std::shared_ptr<Flicker::Shader> shader;
    if (tryGetLoadedAsset<Flicker::Shader>(name, m_LoadedShaders, shader))
    {
        return shader;
    }

    std::string path = getPathToAsset(name, "shaders");

    std::string vertexShaderSource = getFileContents(path + ".vs");
    std::string fragmentShaderSource = getFileContents(path + ".fs");

    shader = std::make_shared<Flicker::Shader>(vertexShaderSource, fragmentShaderSource);

    m_LoadedShaders[name] = shader;

    return shader;
}

std::shared_ptr<Flicker::Node> Flicker::Assets::loadModel(std::string name)
{
    std::shared_ptr<Flicker::Node> model;
    if (tryGetLoadedAsset<Flicker::Node>(name, m_LoadedModels, model))
    {
        return model;
    }

    std::string path = getPathToAsset(name, "models");

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs); 
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << importer.GetErrorString() << std::endl;
        abort();
        return model;
    }

    model = Flicker::parse_scene(scene, path);

    m_LoadedModels[name] = model;

    return model;
}

std::shared_ptr<Flicker::Texture> Flicker::Assets::loadTexture(std::string folder, std::string name)
{
    std::string path = getPathToAsset(name, folder);
    return loadTextureByPath(path);
}

std::shared_ptr<Flicker::Texture> Flicker::Assets::loadTexture(std::string name)
{
    std::string path = getPathToAsset(name, "textures");
    return loadTextureByPath(path);
}

std::shared_ptr<Flicker::Texture> Flicker::Assets::loadTextureByPath(std::string path)
{
    std::shared_ptr<Texture> texture;
    if (tryGetLoadedAsset<Texture>(path, m_LoadedTextures, texture))
    {
        return texture;
    }

    int width, height, n;
    unsigned char* textureData = stbi_load(path.c_str(), &width, &height, &n, 0);

    assert(textureData);

    texture = std::make_shared<Texture>(width, height, textureData);

    m_LoadedTextures[path] = texture;

    stbi_image_free(textureData);

    return texture;
}

std::string Flicker::Assets::getFileContents(std::string filePath)
{
    std::ifstream ifs(filePath);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

    return content;
}

std::string Flicker::Assets::getPathToAsset(const std::string& name, const std::string& subfolder)
{
    std::stringstream ss;
    ss << ASSETS_PATH << '/';
    if (subfolder.length() > 0)
    {
        ss << subfolder << '/';
    }

    ss << name;

    return ss.str();
}