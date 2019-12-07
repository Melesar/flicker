#pragma once
#include <vector>

struct aiScene;

namespace Flicker
{
    class Mesh;

    class Model
    {
    public:
        Model(const aiScene* scene);
        virtual ~Model();

        size_t meshesCount() const;
        const Mesh& getMesh(size_t index) const;

    private:

        void processNode(aiNode* node, const aiScene* scene);
        void processMesh(aiMesh* mesh, const aiScene* scene);

    private:

        std::vector<Mesh> m_Meshes;
    };
}