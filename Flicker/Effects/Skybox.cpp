#include "Skybox.hpp"
#include "Material/SkyboxMaterial.hpp"

void Flicker::Skybox::draw(const glm::mat4x4& view, const glm::mat4x4& projection)
{
    glBindVertexArray(m_VAO);
    m_Material->setViewProjection(view, projection);
    m_Material->use();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    m_Material->reset();
    glBindVertexArray(0);
}

Flicker::Skybox::Skybox(const std::shared_ptr<Cubemap>& cubemap)
{
    m_Material = std::make_unique<SkyboxMaterial>(cubemap);

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_SkyboxVertices), &m_SkyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glBindVertexArray(0); 
}

Flicker::Skybox::~Skybox()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}