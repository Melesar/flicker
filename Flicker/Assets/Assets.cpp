#include "Assets.hpp"
#include "Shader/Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

std::unordered_map<std::string, std::shared_ptr<Flicker::Shader>> Flicker::Assets::m_LoadedShaders;

std::shared_ptr<Flicker::Shader> Flicker::Assets::loadShader(std::string name)
{
    auto loadedShaderIter = m_LoadedShaders.find(name);
    if (loadedShaderIter != m_LoadedShaders.end())
    {
        return (*loadedShaderIter).second;
    }

    std::stringstream ss;
    ss << ASSETS_PATH << "/shaders/" << name;

    std::string vertexShaderSource = getFileContents(ss.str() + ".vs");
    std::string fragmentShaderSource = getFileContents(ss.str() + ".fs");

    std::shared_ptr<Flicker::Shader> shader = std::make_shared<Flicker::Shader>(vertexShaderSource, fragmentShaderSource);

    m_LoadedShaders[name] = shader;

    return shader;
}

std::string Flicker::Assets::getFileContents(std::string filePath)
{
    std::ifstream ifs(filePath);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

    return content;
}
