#pragma once

#include "PointLight.hpp"

#define UNIFORMS_PACK(index) \
            "pointLights["#index"].position",\
            "pointLights["#index"].ambient",\
            "pointLights["#index"].diffuse",\
            "pointLights["#index"].specular",\
            "pointLights["#index"].constant",\
            "pointLights["#index"].linear",\
            "pointLights["#index"].quadrant",\

namespace Flicker
{
    class LightingData
    {
    public:

        void buildLightingBuffer();

        PointLight* addPointLight(glm::vec3 position = {0, 0, 0});

        void setPointLightPosition(int lightIndex, glm::vec3 position);

        int pointLightsCount() const;

        LightingData();
        ~LightingData() = default;

    private:

        GLint getBufferSize() const;

    private:

        std::vector<PointLight> m_PointLights;

        static const int NUM_VARS = 7;
        const int BUFFER_BINDING = 1;

        bool m_IsBuilt {false};

        GLuint m_LightsUBO;
        GLuint m_ProgramID;

        GLchar* m_UniformNames[NUM_VARS * NUM_POINT_LIGHTS] = 
        {
            UNIFORMS_PACK(0)
            UNIFORMS_PACK(1)
            UNIFORMS_PACK(2)
            UNIFORMS_PACK(3)
        };
    };

    struct PointLightData
    {
        glm::vec3 position {0, 0, 0};

        glm::vec3 ambient {0, 0, 0};
        glm::vec3 diffuse {0, 0, 0};
        glm::vec3 specular {0, 0, 0};

        float constant {0};
        float linear {0};
        float quadrant {0};

        PointLightData() = default;

        PointLightData(const PointLight& light)
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