#pragma once
#include "Light.hpp"

namespace Flicker
{
    struct DirectionalLight : public Light
    {
        glm::vec3 direction {0, 0, 1};
    };
}