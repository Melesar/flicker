#include "ForwardRenderer.hpp"
#include "Assets/Assets.hpp"

Flicker::ForwardRenderer::ForwardRenderer(GLFWwindow* window) : Renderer(window) 
{

}

void Flicker::ForwardRenderer::renderModel(Flicker::Model* model, Flicker::Shader* shader)
{
    
}

void Flicker::ForwardRenderer::renderScene()
{
    renderModel(m_Model.get(), m_Shader.get());
}