#include <glad/glad.h>
#include <cassert>
#include "Renderer.hpp"
#include "Assets/Assets.hpp"

void Flicker::Renderer::render()
{
    glClearColor(0.14f, 0.43f, 0.85f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderScene();
}

void Flicker::Renderer::onWindowResize(GLFWwindow* window, int width, int height)
{
    m_Width = width;
    m_Height = height;
    
    glViewport(0, 0, m_Width, m_Height);
}

Flicker::Renderer::Renderer(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);

    assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

    glfwGetWindowSize(window, &m_Width, &m_Height);

    glViewport(0, 0, m_Width, m_Height);

    m_Model = Flicker::Assets::loadModel("teapot.fbx");

    m_Shader = Flicker::Assets::loadShader("lit");

    // glfwSetFramebufferSizeCallback(window, &onWindowResize);
}

