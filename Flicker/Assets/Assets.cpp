#include "Assets.hpp"
#include "Shader/Shader.hpp"

std::unordered_map<std::string, std::shared_ptr<Flicker::Shader>> Flicker::Assets::m_LoadedShaders;

std::shared_ptr<Flicker::Shader> Flicker::Assets::loadShader(std::string path)
{
    return std::make_shared<Shader>();
}

void Flicker::Assets::get()
{
    
}
