#include "Models/Model.hpp"
#include "ForwardRenderer.hpp"
#include "Assets/Assets.hpp"
#include "Shader/Shader.hpp"
#include "Transform/Camera.hpp"

Flicker::ForwardRenderer::ForwardRenderer(GLFWwindow* window) : Renderer(window) 
{
}

void Flicker::ForwardRenderer::renderModel(Flicker::Model* model, Camera* camera)
{
    glm::mat4x4 viewProjMatrix = camera->worldToClipMatrix();

    glBindBuffer(GL_UNIFORM_BUFFER, m_CameraUBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4x4), glm::value_ptr(viewProjMatrix));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4x4), sizeof(glm::vec3), glm::value_ptr(camera->transform.position));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    m_Model->draw();
}

void Flicker::ForwardRenderer::renderScene(Camera* camera)
{
    renderModel(m_Model.get(), camera);
}