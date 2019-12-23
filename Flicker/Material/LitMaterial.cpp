#include "LitMaterial.hpp"
#include "Assets/Assets.hpp"
#include "Shader/Shader.hpp"
#include "Texture/Texture.hpp"

Flicker::LitMaterial::LitMaterial()
{
    m_Shader = Flicker::Assets::loadShader("lit");

    m_ModelMatrixId = m_Shader->getUniformId("modelMatrix");
    m_ColorId = m_Shader->getUniformId("color");

    // m_DiffuseId = m_Shader->getUniformId("diffuse");
}

void Flicker::LitMaterial::setProperties()
{
    Material::setProperties();
    m_Shader->setVector4(m_ColorId, m_CurrentColor);

    if (m_DiffuseTexture != nullptr)
    {
        glActiveTexture(DIFFUSE_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, m_DiffuseTexture->id());
    }

    if (m_SpecularTexture != nullptr)
    {
        glActiveTexture(SPECULAR_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, m_SpecularTexture->id());
    }
}

void Flicker::LitMaterial::setDiffuseTexture(const Texture* texture)
{
    m_DiffuseTexture = texture;
}

void Flicker::LitMaterial::setSpecularTexture(const Texture* texture)
{
    m_SpecularTexture = texture;
}

void Flicker::LitMaterial::setColor(glm::vec4 color)
{
    m_CurrentColor = color;
}