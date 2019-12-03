#pragma once 
#include "Renderer.hpp"

namespace Flicker
{
    class ForwardRenderer : public Renderer
    {
    public:

        ForwardRenderer(GLFWwindow* window);
        virtual ~ForwardRenderer() = default;

    protected:

        void renderScene() override;
    };
}