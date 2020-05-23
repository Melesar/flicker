#include "pch.hpp"
#include "OpenGl.hpp"

GLuint create_shader(GLenum shaderType, const std::string& source);

bool check_program_for_errors(GLuint program, GLint flag, char* errorMessage);
bool check_shader_for_errors(GLuint shader, GLint flag, char* errorMessage);

Flicker::Shader Flicker::OpenGL::load_shader(const ShaderSources& sources)
{
    Shader shader;
    shader.ProgramId = glCreateProgram();
    
    shader.VertexShader = create_shader(GL_VERTEX_SHADER, sources.VertexShaderSource);
    shader.FragmentShader = create_shader(GL_FRAGMENT_SHADER, sources.FragmentShaderSource);

    glAttachShader(shader.ProgramId, shader.VertexShader);
    glAttachShader(shader.ProgramId, shader.FragmentShader);

    glLinkProgram(shader.ProgramId);

    assert(check_program_for_errors(shader.ProgramId, GL_LINK_STATUS, "Error linking program: "));

    glValidateProgram(shader.ProgramId);

    assert(check_program_for_errors(shader.ProgramId, GL_VALIDATE_STATUS, "Program is invalid: "));
}

void Flicker::OpenGL::use_shader(const Shader& shader)
{
    glUseProgram(shader.ProgramId);
}

void Flicker::OpenGL::delete_shader(const Shader& shader)
{
    glDetachShader(shader.ProgramId, shader.VertexShader);
    glDetachShader(shader.ProgramId, shader.FragmentShader);

    glDeleteShader(shader.VertexShader);
    glDeleteShader(shader.FragmentShader);

    glDeleteProgram(shader.ProgramId);
}

GLuint create_shader(GLenum shaderType, const std::string& source)
{
    GLuint shader = glCreateShader(shaderType);

    assert(shader != 0);

    const GLchar* shaderSourceStrings[1] = {source.c_str()};
    GLint sourcesNum[1] = {static_cast<GLint>(source.length())};

    glShaderSource(shader, 1, shaderSourceStrings, sourcesNum);

    glCompileShader(shader);

    assert(check_shader_for_errors(shader, GL_COMPILE_STATUS, "Error: shader compilation failed: "));

    return shader;
}

bool check_program_for_errors(GLuint program, GLint flag, char* errorMessage)
{
    GLint success = 0;
    glGetProgramiv(program, flag, &success);

    if (success == GL_TRUE)
    {
        return true;
    }

    GLchar error [1024];
    glGetProgramInfoLog(program, sizeof error, nullptr, error);

    std::cerr << errorMessage << error << std::endl;
    return false;
}

bool check_shader_for_errors(GLuint shader, GLint flag, char* errorMessage)
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