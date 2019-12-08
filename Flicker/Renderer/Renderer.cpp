#include "Renderer.hpp"
#include "Assets/Assets.hpp"
#include "Transform/Camera.hpp"
#include "Models/Model.hpp"
#include "Material/LitMaterial.hpp"
#include "Transform/Transform.hpp"

void Flicker::Renderer::render(Camera* camera)
{
    glClearColor(0.14f, 0.43f, 0.85f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderScene(camera);
}

void Flicker::Renderer::onWindowResize(GLFWwindow* window, int width, int height)
{
    m_Width = width;
    m_Height = height;
    
    glViewport(0, 0, m_Width, m_Height);
}

void Flicker::Renderer::setupUniformBuffers()
{
    glGenBuffers(1, &m_MatricesUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, m_MatricesUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4x4), nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_MatricesUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

Flicker::Renderer::Renderer(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);

    assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

    glfwGetWindowSize(window, &m_Width, &m_Height);

    glViewport(0, 0, m_Width, m_Height);

    setupUniformBuffers();

    m_Model = Flicker::Assets::loadModel("teapot.fbx");
    m_Model->getMaterial<LitMaterial>(0)->setColor({1, 0.534, 0.874, 1});
    Flicker::Transform& modelTransform = m_Model->transform;
    modelTransform.position = {0, -1, -3};

    // glfwSetFramebufferSizeCallback(window, &onWindowResize);
}

