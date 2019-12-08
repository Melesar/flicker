#include <assimp/scene.h>
#include "Models/Model.hpp"
#include "ForwardRenderer.hpp"
#include "Assets/Assets.hpp"
#include "Shader/Shader.hpp"

Flicker::ForwardRenderer::ForwardRenderer(GLFWwindow* window) : Renderer(window) 
{
}

void Flicker::ForwardRenderer::renderModel(Flicker::Model* model, Flicker::Shader* shader)
{
    GLint colorId = shader->getUniformId("color");
    GLint transformId = shader->getUniformId("transform");

    shader->use();
    shader->setVector4(colorId, {1, 0.534, 0.874, 1});

    glm::mat4x4 modelMatrix = glm::translate(glm::vec3{0, 0, -5});
    glm::mat4x4 viewMatrix = glm::mat4x4(1.0f);
    glm::mat4x4 projMatrix = glm::perspective(glm::radians(60.f), 800.f/600.f, 0.1f, 100.f);

    shader->setMatrix(transformId, projMatrix * viewMatrix * modelMatrix);

    model->bind();
    glDrawElements(GL_TRIANGLES, model->indexCount(), GL_UNSIGNED_INT, 0);
}

void Flicker::ForwardRenderer::renderScene()
{
    renderModel(m_Model.get(), m_Shader.get());
}