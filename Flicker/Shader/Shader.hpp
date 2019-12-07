#pragma once 
#include <string>
#include <GLAD/glad.h>


namespace Flicker
{
    class Shader
    {
    public:
        Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
        ~Shader();

        void use();

        GLuint getID() const;

        void setInt(char* name, int value);
        void setFloat(char* name, float value);
        // void setTexture(char* name, Texture* value);

        GLint getUniformId(char* name);

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