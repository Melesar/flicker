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

    struct PointLightUniformData
    {
        glm::vec3 position {0, 0, 0};

        glm::vec3 ambient {0, 0, 0};
        glm::vec3 diffuse {0, 0, 0};
        glm::vec3 specular {0, 0, 0};

        float constant {0};
        float linear {0};
        float quadrant {0};

        PointLightUniformData()
        {

        }

        PointLightUniformData(const PointLight& light)
        {
            position = light.transform.position;

            ambient = light.ambient;
            diffuse = light.diffuse;
            specular = light.specular;

            constant = light.constant;
            linear = light.linear;
            quadrant = light.quadrant;
        }
    };
}