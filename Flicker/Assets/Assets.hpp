#pragma once 
#include <memory>
#include <string>
#include <unordered_map>

namespace Flicker
{
    class Shader;

    class Assets
    {
    public:

        static void get();

        static std::shared_ptr<Shader> loadShader(std::string name); 

    private:
        Assets();

        static std::unordered_map<std::string, std::shared_ptr<Shader>> m_LoadedShaders;
    };
}

