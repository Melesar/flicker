#pragma once 
#include <unordered_map>

namespace Flicker
{
    class Shader;
    class Model;
    class Node;
    class Texture;
    class Cubemap;

    class Assets
    {
    private:
    
        const static int SKYBOX_FACES = 6;

    public:

        static std::shared_ptr<Shader> loadShader(std::string name);

        static std::shared_ptr<Node> loadModel(std::string name);

        static std::shared_ptr<Texture> loadTexture(std::string name);
        static std::shared_ptr<Texture> loadTexture(std::string folder, std::string name);
        static std::shared_ptr<Texture> loadTextureByPath(std::string path);

        static std::shared_ptr<Cubemap> loadSkybox(std::string folder, const std::array<std::string, SKYBOX_FACES>& faces);

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
        static std::unordered_map<std::string, std::shared_ptr<Node>> m_LoadedModels;
        static std::unordered_map<std::string, std::shared_ptr<Texture>> m_LoadedTextures;
    };
}

