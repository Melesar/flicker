#include "OpenGLRenderer.hpp"
#include <Data/Containers.hpp>
#include <Data/Components.hpp>
#include "pch.hpp"

Flicker::OpenGLRenderer::OpenGLRenderer(const WindowHandle& windowHandle, Flicker::RenderingWorld& renderingWorld, Flicker::Scene& scene)
    : m_WindowHandle(windowHandle), m_RenderingWorld(renderingWorld), m_Scene(scene)
{
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, m_WindowHandle.Width, m_WindowHandle.Height);
}

Flicker::OpenGLRenderer::~OpenGLRenderer()
{ }

void Flicker::OpenGLRenderer::render()
{
    glClearColor(0.5f, 0.2f, 0.8f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}