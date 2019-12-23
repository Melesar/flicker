#include "LitMaterial.hpp"
#include "Assets/Assets.hpp"
#include "Shader/Shader.hpp"
#include "Texture/Texture.hpp"

Flicker::LitMaterial::LitMaterial()
{
    m_Shader = Flicker::Assets::loadShader("lit");

    m_ModelMatrixId = m_Shader->getUniformId("modelMatrix");
    m_DiffuseColorId = m_Shader->getUniformId("material.diffuseColor");
    m_SpecularColorId = m_Shader->getUniformId("material.specularColor");
    m_ShininessId = m_Shader->getUniformId("material.shininess");
}

void Flicker::LitMaterial::setProperties()
{
    Material::setProperties();
    
    m_Shader->setVector4(m_DiffuseColorId, m_DiffuseColor);
    m_Shader->setVector4(m_SpecularColorId, m_SpecularColor);
    m_Shader->setFloat(m_ShininessId, m_Shininess);

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

void Flicker::LitMaterial::setDiffuseColor(glm::vec4 color)
{
    m_DiffuseColor = color;
}

void Flicker::LitMaterial::setSpecularColor(glm::vec4 color)
{
    m_SpecularColor = color;
}

void Flicker::LitMaterial::setShininess(float shininess)
{
    m_Shininess = shininess;
}
