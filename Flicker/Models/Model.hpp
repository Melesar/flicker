#pragma once
#include "Scene/Node.hpp"

namespace Flicker
{
    class Mesh;
    class Material;


    class Model : public Node
    {
    public:
        Model(const aiNode* node, const aiScene* scene, Node* parent);
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

        void processSingleNode(const aiNode* node, const aiScene* scene);
        void processMesh(const aiMesh* mesh, const aiScene* scene);

        void createBuffers();
        void createBuffers(size_t meshIndex);

    private:

        std::vector<Mesh> m_Meshes;
        std::vector<std::unique_ptr<Material>> m_Materials;
        std::vector<std::unique_ptr<Model>> m_Children;

        GLuint m_VAO;

        std::unique_ptr<GLuint> m_VertexBuffers;
        std::unique_ptr<GLuint> m_IndexBuffers;
    };
}