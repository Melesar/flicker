#include "pch.hpp"
#include "Application.hpp"
#include "ECS/TranformationSystem.hpp"
#include "ECS/MeshRenderingSystem.hpp"
#include "Assets/Assets.hpp"
#include "Assets/AssetsStorage.hpp"
#include "OpenGL/OpenGl.hpp"

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_IsRunning = true;
}

Flicker::Application::~Application()
{
    glfwTerminate();
}

void Flicker::Application::run()
{
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    EntityManager entityManager;
    AssetsStorage assetsStorage;
    assetsStorage.addShader("lit");
    SystemQueue systemsQueue(entityManager);

    Flicker::load_model("teapot.fbx", entityManager, assetsStorage);

    while (m_IsRunning && !glfwWindowShouldClose(m_WindowHandle))
    {
        systemsQueue.update(0.33f);
        glfwPollEvents();
        glfwSwapBuffers(m_WindowHandle);
    }
}