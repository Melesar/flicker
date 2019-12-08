#include "Transform.hpp"

glm::mat4x4 Flicker::Transform::localToWorldMatrix() const
{
    //TODO add support for rotations
    glm::mat4x4 localTRS = glm::translate(position);
    localTRS = glm::scale(localTRS, scale);
    Transform* parent = this->parent;
    while(parent != nullptr)
    {
        localTRS *= parent->localToWorldMatrix();
        parent = parent->parent;
    }

    return localTRS;
}

void Flicker::Transform::setParent(Transform& parent)
{
    if (this->parent == &parent)
    {
        return;
    }

    this->parent = &parent;
    parent.children.push_back(*this);
}

void Flicker::Transform::addChild(Transform& child)
{
    child.parent = this;
    children.push_back(child);
}

Flicker::Transform& Flicker::Transform::getParent()
{
    return *parent;
}

Flicker::Transform& Flicker::Transform::getChild(int index)
{
    assert(index >= 0 && index < childCount());

    return children[index];
}

int Flicker::Transform::childCount() const
{
    return children.size();
}

Flicker::Transform::Transform() : position({0, 0, 0}), rotation({0, 0, 0}), scale({1, 1, 1})
{

}