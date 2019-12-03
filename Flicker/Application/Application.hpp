#pragma once 
#include <memory>
#include <GLFW/glfw3.h>


namespace Flicker
{
    class Renderer;

    class Application
    {
    public:
        
        Application();
        virtual ~Application();

        void run();

    private:

        bool m_ShouldClose {false};

        GLFWwindow* m_Window;
        std::unique_ptr<Renderer> m_Renderer;
        // std::unique_ptr<Input> m_Input;
        // std::unique_ptr<Camera> m_Camera;
    };
}