#pragma once

namespace Flicker
{
    class Shader;

    class Material
    {
    public:
        virtual ~Material() = default;

        virtual void use();

        void setModelMatrix(glm::mat4x4 model);

    protected:

        Material() = default;

    protected:

        std::shared_ptr<Shader> m_Shader;
    
        glm::mat4x4 m_ModelMatrix;

        GLuint m_ModelMatrixId;
        
    };
}