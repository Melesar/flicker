#pragma once
#include "Node.hpp"
#include "Light/LightingData.hpp"

namespace Flicker
{
    class Light;
    class Model;
    class Skybox;

    class Scene
    {
    public:

        void update(float deltaTime);

        const std::vector<std::unique_ptr<Model>>& getModels() const;

        Skybox* getSkybox() const;

        Scene();
        virtual ~Scene();

    private:
        Node m_Root;
        LightingData m_LightingData;

        void addNode(Node* node);
        void addModels(Node* parent);

        void createSkybox(const std::array<std::string, 6>& faces);

        std::unique_ptr<Skybox> m_Skybox;
        std::vector<std::unique_ptr<Light>> m_Lights;
        std::vector<std::unique_ptr<Model>> m_Models;
    };
}