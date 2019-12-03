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


        virtual void renderScene() = 0;

        virtual void onWindowResize(GLFWwindow* window, int width, int height);

    protected:

        int m_Width, m_Height;
    };
}