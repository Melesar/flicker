#pragma once
#include "Transform/Transform.hpp"

struct aiScene;

namespace Flicker
{
    class Mesh;
    class Material;

    class Model
    {
    public:
        Model(const aiScene* scene);
        virtual ~Model();

        void bind() const;
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

        void processNode(aiNode* node, const aiScene* scene);
        void processMesh(aiMesh* mesh, const aiScene* scene);

        void createBuffers();
        void createBuffers(size_t meshIndex);

    public:

        Transform transform;

    private:

        std::vector<Mesh> m_Meshes;
        std::vector<std::unique_ptr<Material>> m_Materials;

        size_t m_IndexCount {0};

        GLuint m_VAO;

        std::unique_ptr<GLuint> m_VertexBuffers;
        std::unique_ptr<GLuint> m_IndexBuffers;
    };
}