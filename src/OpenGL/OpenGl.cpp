#include "pch.hpp"
#include "OpenGl.hpp"

GLuint gl_create_shader(GLenum shaderType, const std::string& source);

bool check_program_for_errors(GLuint program, GLint flag, char* errorMessage);
bool check_shader_for_errors(GLuint shader, GLint flag, char* errorMessage);

Flicker::Shader Flicker::OpenGL::create_shader(const ShaderSources& sources)
{
    Shader shader;
    shader.ProgramId = glCreateProgram();
    
    shader.VertexShader = gl_create_shader(GL_VERTEX_SHADER, sources.VertexShaderSource);
    shader.FragmentShader = gl_create_shader(GL_FRAGMENT_SHADER, sources.FragmentShaderSource);

    glAttachShader(shader.ProgramId, shader.VertexShader);
    glAttachShader(shader.ProgramId, shader.FragmentShader);

    glLinkProgram(shader.ProgramId);

    assert(check_program_for_errors(shader.ProgramId, GL_LINK_STATUS, "Error linking program: "));

    glValidateProgram(shader.ProgramId);

    assert(check_program_for_errors(shader.ProgramId, GL_VALIDATE_STATUS, "Program is invalid: "));

    return shader;
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

GLuint gl_create_shader(GLenum shaderType, const std::string& source)
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

Flicker::Mesh Flicker::OpenGL::createMesh(const std::vector<Flicker::Vertex> vertices, const std::vector<size_t> indices)
{
    Flicker::Mesh mesh;
    mesh.NumIndices = indices.size();
    glGenBuffers(1, &mesh.VertexBuffer);
    glGenBuffers(1, &mesh.IndexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Flicker::Vertex), vertices.data(), GL_STATIC_DRAW);

    int stride = 8 * sizeof(float);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);

    return mesh;
}

GLint Flicker::OpenGL::get_shader_property_id(const Flicker::Shader& shader, const char* propertyName)
{
    return glGetUniformLocation(shader.ProgramId, propertyName);
}
