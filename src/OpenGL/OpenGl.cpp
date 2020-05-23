#include "pch.hpp"
#include "OpenGl.hpp"

Flicker::Shader Flicker::OpenGL::load_shader(const ShaderSources& sources)
{
    Shader shader;
    shader.ProgramId = glCreateProgram();
    
    shader.VertexShader = createShader(GL_VERTEX_SHADER, sources.VertexShaderSource);
    shader.FragmentShader = createShader(GL_FRAGMENT_SHADER, sources.FragmentShaderSource);

    glAttachShader(shader.ProgramId, shader.VertexShader);
    glAttachShader(shader.ProgramId, shader.FragmentShader);

    glLinkProgram(m_Program);

    assert(checkProgramForErrors(GL_LINK_STATUS, "Error linking program: "));

    glValidateProgram(m_Program);

    assert(checkProgramForErrors(GL_VALIDATE_STATUS, "Program is invalid: "));
}