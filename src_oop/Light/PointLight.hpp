#pragma once
#include "Light.hpp"

namespace Flicker
{
    struct PointLight : public Light
    {
        float constant {POINT_LIGHT_CONSTANT_ATTENUATION};
        float linear {POINT_LIGHT_LINEAR_ATTENUATION};
        float quadrant {POINT_LIGHT_QUADRATIC_ATTENUATION};
    };
}