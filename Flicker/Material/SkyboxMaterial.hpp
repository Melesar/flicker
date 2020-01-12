#pragma once
#include "Material.hpp"

namespace Flicker
{
    class Cubemap;

    class SkyboxMaterial : public Material
    {
    public:

        SkyboxMaterial(const std::shared_ptr<Cubemap>& cubemap);

        void setViewProjection(const glm::mat4x4& view, const glm::mat4x4& projection);
        void setProperties() override;
        void reset() override;

    private:

        glm::mat4x4 m_View, m_Projection;
        GLint m_ViewId, m_ProjectionId;
        std::shared_ptr<Cubemap> m_Cubemap;
    };
}