#include "LitMaterial.hpp"
#include "Assets/Assets.hpp"
#include "Shader/Shader.hpp"

Flicker::LitMaterial::LitMaterial()
{
    m_Shader = Flicker::Assets::loadShader("lit");

    m_ModelMatrixId = m_Shader->getUniformId("modelMatrix");
    m_ColorId = m_Shader->getUniformId("color");

    GLint bufferSize;
    glGetActiveUniformBlockiv(m_Shader->getID(), 1, GL_UNIFORM_BLOCK_DATA_SIZE, &bufferSize);

    std::cout << "Block size: " << bufferSize << std::endl;

    const char* puniform = "pointLights[0].linear";
    unsigned int index;
    glGetUniformIndices(m_Shader->getID(), 1, &puniform, &index);
    int offset;
    glGetActiveUniformsiv(m_Shader->getID(), 1, &index, GL_UNIFORM_OFFSET, &offset);

    std::cout << "Constant offset " << offset << std::endl;
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