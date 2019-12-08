#pragma once 
#include "Transform/Transform.hpp"

namespace Flicker
{
    struct Light
    {
        glm::vec3 ambient {0.05f, 0.05f, 0.05f};
        glm::vec3 diffuse {1.f, 1.f, 1.f};
        glm::vec3 specular {1.f, 1.f, 1.f};

        Transform transform;
    };

}