#include "Renderer.hpp"
#include "Assets/Assets.hpp"
#include "Scene/Camera.hpp"
#include "Models/Model.hpp"
#include "Material/LitMaterial.hpp"
#include "Scene/Node.hpp"
#include "Light/LightingData.hpp"

void Flicker::Renderer::render(Camera* camera, Scene* scene)
{
    glClearColor(0.14f, 0.43f, 0.85f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderScene(camera, scene);
}

void Flicker::Renderer::onWindowResize(GLFWwindow* window, int width, int height)
{
    m_Width = width;
    m_Height = height;
    
    glViewport(0, 0, m_Width, m_Height);
}

void Flicker::Renderer::setupUniformBuffers()
{
    glGenBuffers(1, &m_CameraUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, m_CameraUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4x4) + sizeof(glm::vec3), nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_CameraUBO);
}

Flicker::Renderer::Renderer(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);

    assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

    glfwGetWindowSize(window, &m_Width, &m_Height);

    glViewport(0, 0, m_Width, m_Height);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); 

    setupUniformBuffers();

    // glfwSetFramebufferSizeCallback(window, &onWindowResize);
}

