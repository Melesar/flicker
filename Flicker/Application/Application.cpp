#include "Application.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Flicker::Application::run()
{
    while(!m_ShouldClose && !glfwWindowShouldClose(m_Window))
    {
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

    glfwMakeContextCurrent(m_Window);

    // m_Renderer = std::make_unique<ForwardRenderer>(m_Window.get());
}

Flicker::Application::~Application()
{
    glfwTerminate();
}

