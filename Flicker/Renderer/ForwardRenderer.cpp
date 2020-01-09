#include "Models/Model.hpp"
#include "ForwardRenderer.hpp"
#include "Assets/Assets.hpp"
#include "Shader/Shader.hpp"
#include "Scene/Camera.hpp"
#include "Light/LightingData.hpp"
#include "Scene/Scene.hpp"
#include "Effects/Skybox.hpp"

Flicker::ForwardRenderer::ForwardRenderer(GLFWwindow* window) : Renderer(window) 
{
}

void Flicker::ForwardRenderer::renderScene(Camera* camera, Scene* scene)
{
    glm::mat4x4 viewProjMatrix = camera->worldToClipMatrix();

    glBindBuffer(GL_UNIFORM_BUFFER, m_CameraUBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4x4), glm::value_ptr(viewProjMatrix));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4x4), sizeof(glm::vec3), glm::value_ptr(camera->worldPosition()));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    Skybox* skybox = scene->getSkybox();
    if (skybox != nullptr)
    {
        glm::mat4x4 view = camera->worldToViewMatrix();
        glm::mat4x4 proj = camera->viewToClipMatrix();
        skybox->draw(view, proj);
    }

    const std::vector<std::unique_ptr<Model>>& models = scene->getModels();
    for(int i = 0; i < models.size(); ++i)
    {
        models[i]->draw();
    }
}