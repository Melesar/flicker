#pragma once
#include "Node.hpp"


namespace Flicker
{
    class Light;
    class Model;

    class Scene
    {
    public:

        void update(float deltaTime);

        Scene();
        virtual ~Scene();

    private:
        Node m_Root;

        std::vector<std::unique_ptr<Light>> m_Lights;
        std::vector<std::unique_ptr<Model>> m_Models;
    };
}