#include "Application.hpp"
#include "Renderer/ForwardRenderer.hpp"

void Flicker::Application::run()
{
    while(!m_ShouldClose && !glfwWindowShouldClose(m_Window))
    {
        m_Renderer->render();
        
        glfwSwapBuffers(m_Window);

        /* Poll for and process events */
        glfwPollEvents();

        // m_Input.update();
    }
}

Flicker::Application::Application()
{
    if (!glfwInit())
    {
        m_ShouldClose = true;
        return;
    }

    m_Window = glfwCreateWindow(800, 600, "Flicker", nullptr, nullptr);
    if (!m_Window)
    {
        m_ShouldClose = true;
        return;
    }

    m_Renderer = std::make_unique<ForwardRenderer>(m_Window);
    
}

Flicker::Application::~Application()
{
    glfwTerminate();
}

