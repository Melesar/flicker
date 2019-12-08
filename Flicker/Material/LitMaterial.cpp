#include "LitMaterial.hpp"
#include "Assets/Assets.hpp"
#include "Shader/Shader.hpp"

Flicker::LitMaterial::LitMaterial()
{
    m_Shader = Flicker::Assets::loadShader("lit");

    m_ModelMatrixId = m_Shader->getUniformId("modelMatrix");
    m_ColorId = m_Shader->getUniformId("color");
}

void Flicker::LitMaterial::use()
{
    Material::use();

    if (m_Shader)
    {
        m_Shader->setVector4(m_ColorId, m_CurrentColor);
    }
}

void Flicker::LitMaterial::setColor(glm::vec4 color)
{
    m_CurrentColor = color;
}