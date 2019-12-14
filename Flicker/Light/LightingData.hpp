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

        void setPointLightPosition(size_t lightIndex, glm::vec3 position);
        glm::vec3 getPointLightPosition(size_t lightIndex);

        int pointLightsCount() const;

        LightingData();
        ~LightingData() = default;

    private:

        GLint getBufferSize() const;

        template<typename T>
        void setPointLightData(size_t lightIndex, int variableID, const T& data, bool bindBuffer = false)
        {
            if (bindBuffer)
            {
                glBindBuffer(GL_UNIFORM_BUFFER, m_LightsUBO);
            }

            glBufferSubData(GL_UNIFORM_BUFFER, m_PointLightUniformOffsets[lightIndex * POINT_LIGHT_NUM_VARS + variableID], sizeof(T), &data);

            if (bindBuffer)
            {
                glBindBuffer(GL_UNIFORM_BUFFER, 0);
            }
        }

        enum
        {
            POINT_LIGHT_POSITION,
            POINT_LIGHT_AMBIENT,
            POINT_LIGHT_DIFFUSE,
            POINT_LIGHT_SPECULAR,
            POINT_LIGHT_CONSTANT,
            POINT_LIGHT_LINEAR,
            POINT_LIGHT_QUADRANT,

            POINT_LIGHT_NUM_VARS
        };

    private:

        std::vector<PointLight> m_PointLights;

        const int BUFFER_BINDING = 1;
        static const int POINT_LIGHT_UNIFORMS_COUNT = NUM_POINT_LIGHTS * POINT_LIGHT_NUM_VARS;

        bool m_IsBuilt {false};

        GLuint m_LightsUBO;
        GLuint m_ProgramID;

        GLint m_PointLightUniformOffsets[POINT_LIGHT_UNIFORMS_COUNT];

        GLchar* m_UniformNames[POINT_LIGHT_UNIFORMS_COUNT] = 
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