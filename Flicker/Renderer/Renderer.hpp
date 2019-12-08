#pragma once

namespace Flicker
{
    class Shader;
    class Model;
    class Camera;

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

        GLuint m_MatricesUBO;

        std::shared_ptr<Model> m_Model;
    };
}