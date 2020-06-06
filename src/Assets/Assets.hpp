#pragma once

#include "Data/Data.hpp"

namespace Flicker
{
    ShaderSources load_shader (const std::string& shaderName);
    void load_model(const std::string& fileName, EntityManager& entityManager, AssetsStorage& assetsStorage);

    std::string get_path_to_asset(const std::string& name, const std::string& subfolder);
    std::string get_file_contents(std::string filePath);
}