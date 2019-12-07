#include "ForwardRenderer.hpp"
#include "Assets/Assets.hpp"

Flicker::ForwardRenderer::ForwardRenderer(GLFWwindow* window) : Renderer(window) 
{
    Flicker::Assets::loadShader("lit");
}

void Flicker::ForwardRenderer::renderScene()
{

}