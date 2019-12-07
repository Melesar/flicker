#pragma once
#include <GLFW/glfw3.h>
#include <memory>

namespace Flicker
{
    class Shader;
    class Model;

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

        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<Model> m_Model;
    };
}