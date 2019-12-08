#include "Material.hpp"
#include "Shader/Shader.hpp"

void Flicker::Material::use()
{
    if (m_Shader)
    {
        m_Shader->use();
        m_Shader->setMatrix(m_ModelMatrixId, m_ModelMatrix);
    }
}

void Flicker::Material::setModelMatrix(glm::mat4x4 model)
{
    m_ModelMatrix = model;
}