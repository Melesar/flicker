#pragma once 
#include <vector>
#include <glm/glm.hpp>

namespace Flicker
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

    class Mesh
    {
    public:

        Mesh();
        Mesh(const std::vector<Vertex> vertices, const std::vector<int> indices);
        virtual ~Mesh();

        void setVertices (const std::vector<Vertex> verts);
        void setIndices (const std::vector<int> indices);

        const std::vector<Vertex>& getVertices() const;
        const std::vector<int>& getIndices() const;

    private:

        std::vector<Vertex> m_Vertices;
        std::vector<int> m_Indices;
    };
}
