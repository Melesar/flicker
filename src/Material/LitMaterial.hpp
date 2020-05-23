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

        void setDiffuseColor(glm::vec4 color);
        void setSpecularColor(glm::vec4 color);
        void setShininess(float shininess);

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

        glm::vec4 m_DiffuseColor {1, 1, 1, 1};
        glm::vec4 m_SpecularColor {1, 1, 1, 1};
        float m_Shininess {1};

        const Texture* m_DiffuseTexture {nullptr};
        const Texture* m_SpecularTexture {nullptr};

        GLuint m_DiffuseColorId, m_SpecularColorId, m_ShininessId;
    };
}