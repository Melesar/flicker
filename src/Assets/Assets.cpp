#include <pch.hpp>
#include "ECS/ECS_impl.hpp"
#include "AssetsStorage.hpp"
#include "Assets.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

#include "assimp_parse.hpp"

Flicker::ShaderSources Flicker::load_shader(const std::string& shaderName)
{
    std::string path = Flicker::get_path_to_asset(shaderName, "shaders");
    return 
    {
        Flicker::get_file_contents(path + ".vs"),
        Flicker::get_file_contents(path + ".fs")
    };
}

void Flicker::load_model(const std::string& fileName, Flicker::EntityManager& entityManager, Flicker::AssetsStorage& assetsStorage)
{
    std::string path = Flicker::get_path_to_asset(fileName, "models");
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs); 
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << importer.GetErrorString() << std::endl;
        abort();
        return;
    }

    Flicker::AssimpAPI::parse(scene, entityManager, assetsStorage);
}


std::string Flicker::get_file_contents(std::string filePath)
{
    std::ifstream ifs(filePath);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

    return content;
}

std::string Flicker::get_path_to_asset(const std::string& name, const std::string& subfolder)
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