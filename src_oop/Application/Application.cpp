#include "Application.hpp"
#include "Renderer/ForwardRenderer.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Camera.hpp"
#include "Input.hpp"

#include <chrono>

void Flicker::Application::run()
{
    float deltaTime = 0.f;
    while(!m_ShouldClose && !glfwWindowShouldClose(m_Window))
    {
        auto start = std::chrono::high_resolution_clock::now();
        
        Input::update();

        m_Scene->update(deltaTime);
        m_Camera->processInput(deltaTime);

        m_Renderer->render(m_Camera.get(), m_Scene.get());
        
        glfwPollEvents();
        glfwSwapBuffers(m_Window);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> frameDuration = end - start;
        deltaTime = frameDuration.count();
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
    
    Input::init(m_Window);

    m_Camera = std::make_unique<Camera>(m_Window);
    m_Renderer = std::make_unique<ForwardRenderer>(m_Window);
    m_Scene = std::make_unique<Scene>();
}

Flicker::Application::~Application()
{
    glfwTerminate();
}

