#pragma once

namespace Flicker
{
    struct ShaderSources
    {
        std::string VertexShaderSource;
        std::string FragmentShaderSource;
    };

    struct Shader
    {
        GLuint ProgramId;
        GLuint VertexShader;
        GLuint FragmentShader;
    };
}