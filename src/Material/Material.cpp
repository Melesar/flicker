#include "Material.hpp"
#include "Shader/Shader.hpp"

void Flicker::Material::use()
{
    if (m_Shader)
    {
        m_Shader->use();
        setProperties();
    }
}

void Flicker::Material::reset()
{
    
}

void Flicker::Material::setProperties()
{
    m_Shader->setMatrix(m_ModelMatrixId, m_ModelMatrix);
}

void Flicker::Material::setModelMatrix(glm::mat4x4 model)
{
    m_ModelMatrix = model;
}