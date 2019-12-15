#pragma once 
#include "Scene/Node.hpp"

namespace Flicker
{
    struct Light : public Node
    {
        glm::vec3 ambient {0.1f, 0.1f, 0.1f};
        glm::vec3 diffuse {1.f, 1.f, 1.f};
        glm::vec3 specular {1.f, 1.f, 1.f};
    };

}