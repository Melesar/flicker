#pragma once
#include "PointLight.hpp"

namespace Flicker
{
    struct LightUniformData
    {
        PointLightUniformData pointLights[NUM_POINT_LIGHTS];
    };
}