#include "Models/Model.hpp"
#include "ForwardRenderer.hpp"
#include "Assets/Assets.hpp"
#include "Shader/Shader.hpp"
#include "Transform/Camera.hpp"
#include "Light/LightingData.hpp"

Flicker::ForwardRenderer::ForwardRenderer(GLFWwindow* window) : Renderer(window) 
{
}

void Flicker::ForwardRenderer::renderModel(Flicker::Model* model, Camera* camera)
{
    glm::mat4x4 viewProjMatrix = camera->worldToClipMatrix();

    glBindBuffer(GL_UNIFORM_BUFFER, m_CameraUBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4x4), glm::value_ptr(viewProjMatrix));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4x4), sizeof(glm::vec3), glm::value_ptr(camera->transform.worldPosition()));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // glm::vec3 pivotPosition = {0, 0, 1};
    // Transform& modelTransform = m_Model->transform;
    // modelTransform.setLocalPosition(pivotPosition + glm::vec3{0, 0, -3*glm::pow(glm::sin(glfwGetTime()), 2)});

    m_ModelParent.setLocalRotation({0, 25.f * glfwGetTime(), 0});
    m_ModelParent.setLocalPosition({0, glm::sin(glfwGetTime()) - 1, -4});

    m_Model->draw();
}

void Flicker::ForwardRenderer::renderScene(Camera* camera)
{
    renderModel(m_Model.get(), camera);
}