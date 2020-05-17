#pragma once

namespace Flicker
{
    class Shader;

    class Material
    {
    public:
        virtual ~Material() = default;

        void use();
        virtual void reset();

        void setModelMatrix(glm::mat4x4 model);

    protected:

        Material() = default;

        virtual void setProperties();

    protected:

        std::shared_ptr<Shader> m_Shader;
    
        glm::mat4x4 m_ModelMatrix;

        GLuint m_ModelMatrixId;
        
    };
}