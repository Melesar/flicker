#pragma once

#include <Data/Data.hpp>

namespace Flicker
{
    namespace OpenGL
    {
        Shader load_shader(const ShaderSources& sources);
        void use_shader(const Shader& shader);
    }
}