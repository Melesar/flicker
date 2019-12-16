#include "model_import.hpp"
#include "Model.hpp"

void parse_node(const aiNode* node, const aiScene* scene, Flicker::Node* parent, glm::mat4& transform)
{
    if (node->mNumMeshes > 0)
    {
        Flicker::Model* model = new Flicker::Model(node, scene, parent);
        model->setTRS(transform);
        model->setParent(parent);      
        parent = model;
        transform = glm::mat4(1.f);
    }
    else
    {
        transform = *reinterpret_cast<const glm::mat4*>(&node->mTransformation) * transform;
    }

    for(size_t i = 0; i < node->mNumChildren; ++i)
    {
        parse_node(node->mChildren[i], scene, parent, transform);
    }
}

std::shared_ptr<Flicker::Node> Flicker::parse_scene(const aiScene* scene)
{
    std::shared_ptr<Node> rootNode = std::make_shared<Node>();

    parse_node(scene->mRootNode, scene, rootNode.get(), glm::mat4(1.f));

    return rootNode;
}