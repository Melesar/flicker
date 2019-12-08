#pragma once

struct aiScene;

namespace Flicker
{
    class Mesh;

    class Model
    {
    public:
        Model(const aiScene* scene);
        virtual ~Model();

        void bind() const;

        size_t indexCount() const;
        size_t meshesCount() const;
        const Mesh& getMesh(size_t index) const;

    private:

        void processNode(aiNode* node, const aiScene* scene);
        void processMesh(aiMesh* mesh, const aiScene* scene);

        void createBuffers();
        void createBuffers(size_t meshIndex);

    private:

        std::vector<Mesh> m_Meshes;

        size_t m_IndexCount {0};

        GLuint m_VAO;

        std::unique_ptr<GLuint> m_VertexBuffers;
        std::unique_ptr<GLuint> m_IndexBuffers;
    };
}