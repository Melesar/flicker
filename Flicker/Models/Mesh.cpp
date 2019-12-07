#include "Mesh.hpp"

Flicker::Mesh::Mesh()
{

}

Flicker::Mesh::Mesh(const std::vector<Flicker::Vertex> vertices, const std::vector<int> indices)
{
    setVertices(vertices);
    setIndices(indices);
}

Flicker::Mesh::~Mesh()
{

}

void Flicker::Mesh::setVertices (const std::vector<Flicker::Vertex> verts)
{
    m_Vertices = verts;
}

void Flicker::Mesh::setIndices (const std::vector<int> indices)
{
    m_Indices = indices;
}

const std::vector<Flicker::Vertex>& Flicker::Mesh::getVertices() const
{
    return m_Vertices;
}

const std::vector<int>& Flicker::Mesh::getIndices() const
{
    return m_Indices;
}