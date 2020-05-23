#include <pch.hpp>
#include "Assets.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

Flicker::ShaderSources Flicker::load_shader(const std::string& shaderName)
{
    std::string path = Flicker::get_path_to_asset(shaderName, "shaders");
    return 
    {
        Flicker::get_file_contents(path + ".vs"),
        Flicker::get_file_contents(path + ".fs")
    };
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