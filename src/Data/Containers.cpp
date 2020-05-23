#include "Containers.hpp"
#include "Data.hpp"

Flicker::ShaderHandle add_shader(Flicker::ShadersStorage& container, Flicker::Shader shader)
{
    assert(container.Count < container.Shaders.size());
    container.Shaders[container.Count++] = shader;
    uint16_t index = container.Count - static_cast<uint16_t>(1);
    return {index, container.Generations[index]};
}