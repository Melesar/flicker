#pragma once 
#include <string>
#include <GLAD/glad.h>
#include <glm/glm.hpp>

namespace Flicker
{
    class Shader
    {
    public:
        Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
        ~Shader();

        void use();

        GLuint getID() const;

        void setInt(GLint id, int value);
        void setFloat(GLint id, float value);
        void setVector4(GLint id, glm::vec4 vec);
        void setMatrix(GLint id, glm::mat4x4 mat);
        // void setTexture(GLint id, Texture* value);

        GLint getUniformId(char* name) const;

    private:

        GLuint createShader(GLenum shaderType, const std::string& source);

        bool checkProgramForErrors(GLint flag, char* errorMessage);
        bool checkShaderForErrors(GLuint shader, GLint flag, char* errorMessage);

    private:

        GLuint m_Program;

        GLuint m_VertexShader;
        GLuint m_FragmentShader;
    };
}