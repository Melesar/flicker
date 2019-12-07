#pragma once
#include <GLFW/glfw3.h>

namespace Flicker
{
    class Renderer
    {
    public: 
        void render();
        Renderer(GLFWwindow* window);
        virtual ~Renderer() = default;

    protected:

        void onWindowResize(GLFWwindow* window, int width, int height);
        
        virtual void renderScene() = 0;

    protected:

        int m_Width, m_Height;
    };
}