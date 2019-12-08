#include "Shader.hpp"
#include <cassert>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

void Flicker::Shader::use()
{
    glUseProgram(m_Program);
}

GLuint Flicker::Shader::getID() const
{
    return m_Program;
}

void Flicker::Shader::setInt(GLint id, int value)
{
    glUniform1i(id, value);
}

void Flicker::Shader::setFloat(GLint id, float value)
{
    glUniform1f(id, value);
}

void Flicker::Shader::setVector4(GLint id, glm::vec4 vec)
{
    glUniform4fv(id, 1, glm::value_ptr(vec));
}

void Flicker::Shader::setMatrix(GLint id, glm::mat4x4 mat)
{
    glUniformMatrix4fv(id, 1, false, glm::value_ptr(mat));
}

GLint Flicker::Shader::getUniformId(char* name) const
{
    return glGetUniformLocation(m_Program, name);    
}

Flicker::Shader::Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    m_Program = glCreateProgram();
    
    m_VertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
    m_FragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(m_Program, m_VertexShader);
    glAttachShader(m_Program, m_FragmentShader);

    glLinkProgram(m_Program);

    assert(checkProgramForErrors(GL_LINK_STATUS, "Error linking program: "));

    glValidateProgram(m_Program);

    assert(checkProgramForErrors(GL_VALIDATE_STATUS, "Program is invalid: "));
}

Flicker::Shader::~Shader()
{  
    glDetachShader(m_Program, m_VertexShader);
    glDetachShader(m_Program, m_FragmentShader);

    glDeleteShader(m_VertexShader);
    glDeleteShader(m_FragmentShader);

    glDeleteProgram(m_Program);
}

GLuint Flicker::Shader::createShader(GLenum shaderType, const std::string& source)
{
    GLuint shader = glCreateShader(shaderType);

    assert(shader != 0);

    const GLchar* shaderSourceStrings[1] = {source.c_str()};
    GLint sourcesNum[1] = {source.length()};

    glShaderSource(shader, 1, shaderSourceStrings, sourcesNum);

    glCompileShader(shader);

    assert(checkShaderForErrors(shader, GL_COMPILE_STATUS, "Error: shader compilation failed: "));

    return shader;
}

bool Flicker::Shader::checkProgramForErrors(GLint flag, char* errorMessage)
{
    GLint success = 0;
    glGetProgramiv(m_Program, flag, &success);

    if (success == GL_TRUE)
    {
        return true;
    }

    GLchar error [1024];
    glGetProgramInfoLog(m_Program, sizeof error, nullptr, error);

    std::cerr << errorMessage << error << std::endl;
    return false;
}

bool Flicker::Shader::checkShaderForErrors(GLuint shader, GLint flag, char* errorMessage)
{
    GLint success = 0;
    glGetShaderiv(shader, flag, &success);

    if (success == GL_TRUE)
    {
        return true;
    }

    GLchar error [1024];
    glGetShaderInfoLog(shader, sizeof error, nullptr, error);

    std::cerr << errorMessage << error << std::endl;
    return false;
}