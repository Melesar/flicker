#include "Model.hpp"
#include "Mesh.hpp"
#include "Material/LitMaterial.hpp"

Flicker::Model::Model(const std::vector<Mesh>& meshes, const std::vector<std::shared_ptr<Material>>& materials)
{
    m_Meshes = meshes;
    m_Materials = materials;

    createBuffers();
}

Flicker::Model::~Model()
{
    glDeleteVertexArrays(1, &m_VAO);
}

void Flicker::Model::draw()
{
    glBindVertexArray(m_VAO);

    for(int i = 0; i < meshesCount(); ++i)
    {
        std::shared_ptr<Material> mat = m_Materials[i];
        Mesh& mesh = m_Meshes[i];

        mat->setModelMatrix(localToWorldMatrix());
        mat->use();

        glDrawElements(GL_TRIANGLES, mesh.trisCount(), GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
}

Flicker::Material* Flicker::Model::getMaterial (int index)
{
    assert(index < meshesCount());

    return m_Materials[index].get();
} 

size_t Flicker::Model::meshesCount() const
{
    return m_Meshes.size();
}

const Flicker::Mesh& Flicker::Model::getMesh(size_t index) const
{
    assert(index < m_Meshes.size());

    return m_Meshes[index];
}

void Flicker::Model::createBuffers()
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    int numMeshes = m_Meshes.size();
    m_VertexBuffers = std::make_unique<GLuint>(numMeshes);
    m_IndexBuffers = std::make_unique<GLuint>(numMeshes);

    glGenBuffers(numMeshes, m_VertexBuffers.get());
    glGenBuffers(numMeshes, m_IndexBuffers.get());

    for(size_t index = 0; index < numMeshes; ++index)
    {
        createBuffers(index);
    }

    glBindVertexArray(0);
}

void Flicker::Model::createBuffers(size_t meshIndex)
{
    Mesh& mesh = m_Meshes[meshIndex];
    const std::vector<Flicker::Vertex>& vertices = mesh.getVertices();
    const std::vector<int>& indices = mesh.getIndices();

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffers.get()[meshIndex]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    int stride = 8 * sizeof(float);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffers.get()[meshIndex]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
}