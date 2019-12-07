#pragma once 
#include <memory>
#include <string>
#include <unordered_map>

namespace Flicker
{
    class Shader;
    class Model;

    class Assets
    {
    public:

        static std::shared_ptr<Shader> loadShader(std::string name); 
        static std::shared_ptr<Model> loadModel(std::string name);

        static std::string getFileContents(std::string fileName);

    private:

        static std::string getPathToAsset(const std::string& name, const std::string& subfolder);

        template<typename T>
        static bool tryGetLoadedAsset(std::string name, const std::unordered_map<std::string, std::shared_ptr<T>>& map, std::shared_ptr<T>& result)
        {
            auto iter = map.find(name);
            if (iter != map.end())
            {
                result = (*iter).second;
                return true;
            } 

            return false;
        }

    private:
        Assets();

        static std::unordered_map<std::string, std::shared_ptr<Shader>> m_LoadedShaders;
        static std::unordered_map<std::string, std::shared_ptr<Model>> m_LoadedModels;
    };
}

