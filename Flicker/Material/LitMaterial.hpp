#pragma once
#include "Material.hpp"

namespace Flicker
{
    class Texture;

    class LitMaterial : public Material
    {
    public:
        LitMaterial();
        virtual ~LitMaterial() = default;

        void setColor(glm::vec4 color);
        void setDiffuseTexture(const Texture* texture);
        void setSpecularTexture(const Texture* texture);

    protected:

        void setProperties() override;
    
    protected:

        enum
        {
            DIFFUSE_TEXTURE = GL_TEXTURE0,
            SPECULAR_TEXTURE,
        };

        glm::vec4 m_CurrentColor {1, 1, 1, 1};

        const Texture* m_DiffuseTexture {nullptr};
        const Texture* m_SpecularTexture {nullptr};

        GLuint m_ColorId, m_DiffuseId, m_SpecularId;
    };
}