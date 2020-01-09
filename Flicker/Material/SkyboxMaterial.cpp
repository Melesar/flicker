#include "SkyboxMaterial.hpp"
#include "Texture/Cubemap.hpp"
#include "Assets/Assets.hpp"
#include "Shader/Shader.hpp"

Flicker::SkyboxMaterial::SkyboxMaterial(const Cubemap* cubemap) : m_Cubemap(cubemap)
{
    m_Shader = Assets::loadShader("skybox");
    m_ViewId = m_Shader->getUniformId("view");
    m_ProjectionId = m_Shader->getUniformId("projection");
}

void Flicker::SkyboxMaterial::setViewProjection(const glm::mat4x4& view, const glm::mat4x4& projection)
{
    m_View = glm::mat4(glm::mat3(view));
    m_Projection = projection;
}

void Flicker::SkyboxMaterial::setProperties()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_Cubemap->id());
    m_Shader->setMatrix(m_ViewId, m_View);
    m_Shader->setMatrix(m_ProjectionId, m_Projection);
    glDepthMask(GL_FALSE);
}

void Flicker::SkyboxMaterial::reset()
{
    glDepthMask(GL_TRUE);
} 