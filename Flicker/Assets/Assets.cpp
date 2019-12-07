#include "Assets.hpp"
#include "Shader/Shader.hpp"
#include "Models/Model.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <fstream>
#include <sstream>
#include <iostream>

std::unordered_map<std::string, std::shared_ptr<Flicker::Shader>> Flicker::Assets::m_LoadedShaders;
std::unordered_map<std::string, std::shared_ptr<Flicker::Model>> Flicker::Assets::m_LoadedModels;

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

std::shared_ptr<Flicker::Model> Flicker::Assets::loadModel(std::string name)
{
    std::shared_ptr<Flicker::Model> model;
    if (tryGetLoadedAsset<Flicker::Model>(name, m_LoadedModels, model))
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

    model = std::make_shared<Model>(scene);

    m_LoadedModels[name] = model;

    return model;
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