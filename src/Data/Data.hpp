#pragma once

namespace Flicker
{
    struct Handle
    {
        size_t Index;
        Handle(size_t index) : Index(index) { } 
    };

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

    struct Material
    {
        Shader ShaderInstance;
        std::unordered_map<GLint, GLfloat> FloatParams;
        std::unordered_map<GLint, glm::vec4> Vec4Params;
        std::unordered_map<GLint, glm::mat4> MatrixParams;
        std::unordered_map<GLint, GLint> TextureParams;

        Material() = default;
        explicit Material (const Shader& shader) : ShaderInstance(shader) {}
    };

    struct Mesh
    {
        GLuint VertexBuffer;
        GLuint IndexBuffer;
        size_t NumIndices;
    };

    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 Uv;

        Vertex() : Position({}), Normal ({}), Uv({}) { }

        Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 uv) 
            : Position(position), Normal (normal), Uv(uv) { }
    };

    struct Texture
    {
        GLuint Id;
        size_t Width, Height;
    };

    enum 
    {
        LIT_SHADER_HANDLE = 0
    };
}