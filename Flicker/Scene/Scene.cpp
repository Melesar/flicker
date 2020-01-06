#include "Scene.hpp"
#include "Models/Model.hpp"
#include "Light/Light.hpp"
#include "Assets/Assets.hpp"

void Flicker::Scene::update(float deltaTime)
{
    Node& model = m_Root.getChild(0);
    model.setLocalPosition({3 * glm::sin(glfwGetTime()), -8, -15});
}

const std::vector<std::unique_ptr<Flicker::Model>>& Flicker::Scene::getModels() const
{
    return m_Models;
}

Flicker::Scene::Scene()
{
    std::shared_ptr<Node> nanosuit = Assets::loadModel("nanosuit/nanosuit.obj");
    nanosuit->setLocalPosition({0, -8, -15});
    addNode(nanosuit.get());

    m_LightingData.createDirectionalLight({1, -1, -1});
    m_LightingData.buildLightingBuffer();
}

Flicker::Scene::~Scene()
{
}

void Flicker::Scene::addNode(Node* node)
{
    node->setParent(&m_Root);

    addModels(node);
}

void Flicker::Scene::addModels(Node* parent)
{
    Model* m = dynamic_cast<Model*>(parent);
    if (m != nullptr)
    {
        m_Models.emplace_back(m);
    }

    for(int i = 0; i < parent->childCount(); ++i)
    {
        addModels(&parent->getChild(i));
    }
}
