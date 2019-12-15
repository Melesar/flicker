#include "Transform.hpp"
#include <glm/gtx/matrix_decompose.hpp>
#include "Utils/utils.hpp"

glm::vec3 translation, scale, skew;
glm::vec4 perspective;
glm::quat rot;

void decomposeMatrix(glm::mat4 matrix)
{
    glm::decompose(matrix, scale, rot, translation, skew, perspective);
}

glm::mat4x4 Flicker::Transform::localToWorldMatrix()
{
    rebuildMatrixIfNeeded();

    return m_LocalToWorld;
}

void Flicker::Transform::setParent(Transform* parent)
{
    if (m_Parent == parent)
    {
        return;
    }

    m_Parent = parent;
    m_IsDirty = true;
    m_Parent->m_Children.push_back(this);
}

Flicker::Transform& Flicker::Transform::getParent()
{
    return *m_Parent;
}

Flicker::Transform& Flicker::Transform::getChild(int index)
{
    assert(index >= 0 && index < childCount());

    return *m_Children[index];
}

int Flicker::Transform::childCount() const
{
    return m_Children.size();
}

glm::vec3 Flicker::Transform::localPosition() const
{
    return m_LocalPosition;
}

glm::vec3 Flicker::Transform::localRotation() const
{
    return m_LocalRotation;
}

glm::vec3 Flicker::Transform::localScale() const
{
    return m_LocalScale;
}

glm::vec3 Flicker::Transform::worldPosition() const
{
    glm::mat4 matrix = getParentMatrix() * glm::translate(m_LocalPosition);

    decomposeMatrix(matrix);

    return translation;
}

glm::vec3 Flicker::Transform::worldRotation() const
{
    glm::mat4 rotationMatrix = glm::rotation_matrix(glm::mat4(1.f), m_LocalRotation);
    glm::mat4 matrix = getParentMatrix() * rotationMatrix;

    decomposeMatrix(matrix);

    return glm::quat_to_euler(glm::conjugate(rot));
}

glm::vec3 Flicker::Transform::worldScale() const
{
    glm::mat4 matrix = getParentMatrix() * glm::scale(m_LocalScale);

    decomposeMatrix(matrix);

    return scale;
}

void Flicker::Transform::setLocalPosition(glm::vec3 position)
{
    m_LocalPosition = position;
    m_IsDirty = true;
}

void Flicker::Transform::setLocalRotation(glm::vec3 rotation)
{
    m_LocalRotation = rotation;
    m_IsDirty = true;
}

void Flicker::Transform::setLocalScale(glm::vec3 scale)
{
    m_LocalScale = scale;
    m_IsDirty = true;
}

void Flicker::Transform::setLocal(glm::vec3 position, glm::vec3 rotation)
{
    m_LocalPosition = position;
    m_LocalRotation = rotation;
    m_IsDirty = true;
}

void Flicker::Transform::setLocal(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    m_LocalPosition = position;
    m_LocalRotation = rotation;
    m_LocalScale = scale;
    m_IsDirty = true;
}

void Flicker::Transform::setWorldPosition(glm::vec3 position)
{
    glm::mat4 matrix = glm::inverse(localToWorldMatrix()) * glm::translate(position);

    decomposeMatrix(matrix);

    setLocalPosition(translation);
}

void Flicker::Transform::setWorldRotation(glm::vec3 rotation)
{
    glm::mat4 matrix = glm::inverse(localToWorldMatrix()) * glm::rotation_matrix(glm::mat4(1.f), rotation);

    decomposeMatrix(matrix);

    setLocalRotation(glm::quat_to_euler(glm::conjugate(rot)));
}

void Flicker::Transform::setWorld(glm::vec3 position, glm::vec3 rotation)
{
    glm::mat4 matrix = glm::trs(position, rotation, {1, 1, 1});
    matrix = glm::inverse(localToWorldMatrix()) * matrix;

    decomposeMatrix(matrix);

    setLocal(translation, glm::quat_to_euler(glm::conjugate(rot)));
}

Flicker::Transform::Transform()
{

}

void Flicker::Transform::rebuildMatrix()
{
    m_LocalToWorld = glm::trs(m_LocalPosition, m_LocalRotation, m_LocalScale);
    m_LocalToWorld = getParentMatrix() * m_LocalToWorld;
}

void Flicker::Transform::rebuildMatrixIfNeeded()
{
    if (m_IsDirty)
    {
        rebuildMatrix();
    }
}

glm::mat4 Flicker::Transform::getParentMatrix() const
{
    glm::mat4 m (1.f);
    Transform* parent = m_Parent;
    while(parent != nullptr)
    {
        m = parent->localToWorldMatrix() * m;
        parent = parent->m_Parent;
    }

    return m;
}