#pragma once

#include <Data/Data.hpp>

namespace Flicker
{
    namespace OpenGL
    {
        Mesh createMesh(const std::vector<Flicker::Vertex> vertices, const std::vector<size_t> indices);

        Shader create_shader(const ShaderSources& sources);
        GLint get_shader_property_id(const Shader& shader, const char* proprtyName);
        void use_shader(const Shader& shader);
        void delete_shader(const Shader& shader);
    }
}