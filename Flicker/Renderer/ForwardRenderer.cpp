#include "Models/Model.hpp"
#include "ForwardRenderer.hpp"
#include "Assets/Assets.hpp"
#include "Shader/Shader.hpp"
#include "Transform/Camera.hpp"

Flicker::ForwardRenderer::ForwardRenderer(GLFWwindow* window) : Renderer(window) 
{
}

void Flicker::ForwardRenderer::renderModel(Flicker::Model* model, Flicker::Shader* shader, Camera* camera)
{
    GLint colorId = shader->getUniformId("color");
    GLint transformId = shader->getUniformId("transform");

    shader->use();
    shader->setVector4(colorId, {1, 0.534, 0.874, 1});

    Flicker::Transform& modelTransform = model->transform;
    modelTransform.position = {0, -1, -3};
    glm::mat4x4 modelMatrix = modelTransform.localToWorldMatrix();
    glm::mat4x4 viewProjMatrix = camera->worldToClipMatrix();

    shader->setMatrix(transformId, viewProjMatrix * modelMatrix);

    model->bind();
    glDrawElements(GL_TRIANGLES, model->indexCount(), GL_UNSIGNED_INT, 0);
}

void Flicker::ForwardRenderer::renderScene(Camera* camera)
{
    renderModel(m_Model.get(), m_Shader.get(), camera);
}