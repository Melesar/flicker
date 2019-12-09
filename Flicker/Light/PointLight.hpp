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
        glm::vec4 position {0, 0, 0, 0};

        glm::vec4 ambient {0, 0, 0, 0};
        glm::vec4 diffuse {0, 0, 0, 0};
        glm::vec4 specular {0, 0, 0, 0};

        float constant {0};
        float linear {0};
        float quadrant {0};

        PointLightUniformData()
        {

        }

        PointLightUniformData(const PointLight& light)
        {
            position = glm::vec4(light.transform.position, 0.f);

            ambient = glm::vec4(light.ambient, 0.f);
            diffuse = glm::vec4(light.diffuse, 0.f);
            specular = glm::vec4(light.specular, 0.f);

            constant = light.constant;
            linear = light.linear;
            quadrant = light.quadrant;
        }
    };
}