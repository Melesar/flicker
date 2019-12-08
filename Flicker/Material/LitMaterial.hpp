#pragma once
#include "Material.hpp"

namespace Flicker
{
    class LitMaterial : public Material
    {
    public:
        LitMaterial();
        virtual ~LitMaterial() = default;

        void use() override;

        void setColor(glm::vec4 color);

    protected:

        glm::vec4 m_CurrentColor {0, 0, 0, 1};

        GLuint m_ColorId, m_DiffuseId, m_SpecularId;
    };
}