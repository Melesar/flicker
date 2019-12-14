#pragma once

#include "Light/PointLight.hpp"

namespace Flicker
{
    class Shader;
    class Model;
    class Camera;
    class LightingData;

    class Renderer
    {
    public: 
        void render(Camera* camera);

        Renderer(GLFWwindow* window);
        virtual ~Renderer() = default;

    protected:

        void onWindowResize(GLFWwindow* window, int width, int height);
        
        virtual void renderScene(Camera* camera) = 0;

    private:

        void setupUniformBuffers();

    protected:

        int m_Width, m_Height;

        GLuint m_CameraUBO, m_LightsUBO;

        Transform m_ModelParent;
        std::unique_ptr<LightingData> m_Lighting;
        std::shared_ptr<Model> m_Model;
    };
}