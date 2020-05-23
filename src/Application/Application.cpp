#include "pch.hpp"
#include "Application.hpp"
#include "Data/Containers.hpp"
#include "Data/Components.hpp"
#include "Renderer/OpenGLRenderer.hpp"

Flicker::Application::Application()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize window!" << std::endl;
        m_IsRunning = false;
        return;
    }

    m_WindowHandle = glfwCreateWindow(800, 600, "Flicker", nullptr, nullptr);
    if (!m_WindowHandle)
    {
        std::cerr << "Failed to initialize window!" << std::endl;
        m_IsRunning = false;
        return;
    }

    glfwMakeContextCurrent(m_WindowHandle);

    m_IsRunning = true;
}

void Flicker::Application::run()
{
    std::unique_ptr<RenderingWorld> renderingWorld = std::make_unique<RenderingWorld>();
    Flicker::Scene* scene = Flicker::create_container<Scene>();
    
    int width, height;
    glfwGetWindowSize(m_WindowHandle, &width, &height);
    WindowHandle handle {static_cast<uint16_t>(width), static_cast<uint16_t>(height)};
    Flicker::OpenGLRenderer renderer(handle, *renderingWorld, *scene);

    while (m_IsRunning && !glfwWindowShouldClose(m_WindowHandle))
    {
        renderer.render();
        
        glfwPollEvents();
        glfwSwapBuffers(m_WindowHandle);
    }

    Flicker::free_container(scene);
}