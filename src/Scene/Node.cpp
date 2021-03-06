#include "Node.hpp"
#include <glm/gtx/matrix_decompose.hpp>
#include "Utils/utils.hpp"

glm::vec3 translation, scale, skew;
glm::vec4 perspective;
glm::quat rot;

void decomposeMatrix(glm::mat4 matrix)
{
    glm::decompose(matrix, scale, rot, translation, skew, perspective);
}

glm::mat4x4 Flicker::Node::localToWorldMatrix() const
{
    return getParentMatrix() * m_LocalToWorld;
}

void Flicker::Node::translateLocal(glm::vec3 offset)
{
    m_LocalPosition += offset;
    rebuildMatrix();
}

void Flicker::Node::translateWorld(glm::vec3 offset)
{
    glm::vec3 localOffset = glm::inverse(localToWorldMatrix()) * glm::vec4(offset, 0);
    m_LocalPosition += localOffset;
    rebuildMatrix();
}

void Flicker::Node::setParent(Node* parent)
{
    if (m_Parent == parent)
    {
        return;
    }

    if (m_Parent != nullptr)
    {
        std::vector<Node*>& children = m_Parent->m_Children;
        for(auto i = children.begin(); i < children.end(); ++i)
        {
            if (*i == this) 
            {
                children.erase(i);
                break;
            }
        }
    }

    m_Parent = parent;
    m_Parent->m_Children.push_back(this);

    rebuildMatrix();
}

Flicker::Node& Flicker::Node::getParent()
{
    return *m_Parent;
}

Flicker::Node& Flicker::Node::getChild(int index)
{
    assert(index >= 0 && index < childCount());

    return *m_Children[index];
}

int Flicker::Node::childCount() const
{
    return m_Children.size();
}

glm::vec3 Flicker::Node::localPosition() const
{
    return m_LocalPosition;
}

glm::vec3 Flicker::Node::localRotation() const
{
    return m_LocalRotation;
}

glm::vec3 Flicker::Node::localScale() const
{
    return m_LocalScale;
}

glm::vec3 Flicker::Node::worldPosition() const
{
    glm::mat4 matrix = getParentMatrix() * glm::translate(m_LocalPosition);

    decomposeMatrix(matrix);

    return translation;
}

glm::vec3 Flicker::Node::worldRotation() const
{
    glm::mat4 rotationMatrix = glm::rotation_matrix(glm::mat4(1.f), m_LocalRotation);
    glm::mat4 matrix = getParentMatrix() * rotationMatrix;

    decomposeMatrix(matrix);

    return glm::quat_to_euler(glm::conjugate(rot));
}

glm::vec3 Flicker::Node::worldScale() const
{
    glm::mat4 matrix = getParentMatrix() * glm::scale(m_LocalScale);

    decomposeMatrix(matrix);

    return scale;
}

glm::vec3 Flicker::Node::forward() const
{
    return localToWorldMatrix() * glm::vec4(m_Forward, 0);
}

glm::vec3 Flicker::Node::up() const
{
    return localToWorldMatrix() * glm::vec4(m_Up, 0);
}

glm::vec3 Flicker::Node::right() const
{
    return glm::cross(up(), forward());
}

void Flicker::Node::setTRS(glm::mat4 trs)
{
    decomposeMatrix(trs);

    m_LocalPosition = translation;
    m_LocalRotation = glm::quat_to_euler(glm::conjugate(rot));
    m_LocalScale = scale;

    rebuildMatrix();
}

void Flicker::Node::setLocalPosition(glm::vec3 position)
{
    m_LocalPosition = position;
    rebuildMatrix();
}

void Flicker::Node::setLocalRotation(glm::vec3 rotation)
{
    m_LocalRotation = rotation;
    rebuildMatrix();
}

void Flicker::Node::setLocalScale(glm::vec3 scale)
{
    m_LocalScale = scale;
    rebuildMatrix();
}

void Flicker::Node::setLocal(glm::vec3 position, glm::vec3 rotation)
{
    m_LocalPosition = position;
    m_LocalRotation = rotation;
    rebuildMatrix();
}

void Flicker::Node::setLocal(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    m_LocalPosition = position;
    m_LocalRotation = rotation;
    m_LocalScale = scale;
    rebuildMatrix();
}

void Flicker::Node::setWorldPosition(glm::vec3 position)
{
    glm::mat4 matrix = glm::inverse(localToWorldMatrix()) * glm::translate(position);

    decomposeMatrix(matrix);

    setLocalPosition(translation);
}

void Flicker::Node::setWorldRotation(glm::vec3 rotation)
{
    glm::mat4 matrix = glm::inverse(localToWorldMatrix()) * glm::rotation_matrix(glm::mat4(1.f), rotation);

    decomposeMatrix(matrix);

    setLocalRotation(glm::quat_to_euler(glm::conjugate(rot)));
}

void Flicker::Node::setWorld(glm::vec3 position, glm::vec3 rotation)
{
    glm::mat4 matrix = glm::trs(position, rotation, {1, 1, 1});
    matrix = glm::inverse(localToWorldMatrix()) * matrix;

    decomposeMatrix(matrix);

    setLocal(translation, glm::quat_to_euler(glm::conjugate(rot)));
}

Flicker::Node::Node()
{

}

Flicker::Node::~Node()
{
    for(size_t i = 0; i < childCount(); ++i)
    {
        delete m_Children[i];
    }
}

void Flicker::Node::rebuildMatrix()
{
    m_LocalToWorld = glm::trs(m_LocalPosition, m_LocalRotation, m_LocalScale);
    m_LocalToWorld = getParentMatrix() * m_LocalToWorld;
}

void Flicker::Node::rebuildMatrixIfNeeded()
{
    if (m_IsDirty)
    {
        rebuildMatrix();
    }
}

glm::mat4 Flicker::Node::getParentMatrix() const
{
    glm::mat4 m (1.f);
    Node* parent = m_Parent;
    while(parent != nullptr)
    {
        m = parent->localToWorldMatrix() * m;
        parent = parent->m_Parent;
    }

    return m;
}