#include "Model.hpp"
#include "Mesh.hpp"

glm::vec3 vec3 (aiVector3D vec)
{
    return {vec.x, vec.y, vec.z}; 
}

glm::vec2 vec2 (aiVector3D vec)
{
    return {vec.x, vec.y};
}

Flicker::Model::Model(const aiScene* scene)
{
    processNode(scene->mRootNode, scene);
    createBuffers();
}

Flicker::Model::~Model()
{
    glDeleteVertexArrays(1, &m_VAO);
}

void Flicker::Model::bind() const
{
    glBindVertexArray(m_VAO);
}

size_t Flicker::Model::meshesCount() const
{
    return m_Meshes.size();
}

size_t Flicker::Model::indexCount() const
{
    return m_IndexCount;
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

void Flicker::Model::processNode(aiNode* node, const aiScene* scene)
{
    for(size_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene);
    }

    for(size_t i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

void Flicker::Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Flicker::Vertex> verts;
    std::vector<int> indices;

    for(size_t i = 0; i < mesh->mNumVertices; i++)
    {
        aiVector3D position = mesh->mVertices[i];
        aiVector3D normal = mesh->mNormals[i];

        Vertex v;
        v.position = vec3(position);
        v.normal = vec3(normal);

        v.uv = mesh->mTextureCoords[0]
        ? vec2(mesh->mTextureCoords[0][i])
        : glm::vec2();

        verts.push_back(v);
    }

    for(size_t i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for(size_t j = 0; j < face.mNumIndices; ++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    m_Meshes.emplace_back(verts, indices);
    m_IndexCount += indices.size();
}
