#pragma once
#include "Scene/Node.hpp"

namespace Flicker
{
    class Mesh;
    class Material;


    class Model : public Node
    {
    public:
        Model(const std::vector<Mesh>& meshes, const std::vector<std::shared_ptr<Material>>& materials);
        virtual ~Model();

        void draw();

        Material* getMaterial(int index);

        size_t indexCount() const;
        size_t meshesCount() const;
        const Mesh& getMesh(size_t index) const;

    public:

        template<typename T>
        T* getMaterial(int index)
        {
            return dynamic_cast<T*>(m_Materials[index].get());
        }

    private:

        void createBuffers();
        void createBuffers(size_t meshIndex);

    private:

        std::vector<Mesh> m_Meshes;
        std::vector<std::shared_ptr<Material>> m_Materials;

        GLuint m_VAO;

        std::unique_ptr<GLuint> m_VertexBuffers;
        std::unique_ptr<GLuint> m_IndexBuffers;
    };
}