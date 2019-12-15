#pragma once

namespace Flicker
{
    class Transform
    {
    public:

        void setParent(Transform* parent);

        Transform& getParent();
        Transform& getChild(int index);
        int childCount() const;  

        glm::vec3 localPosition() const;
        glm::vec3 localRotation() const;
        glm::vec3 localScale() const;

        glm::vec3 worldPosition() const;
        glm::vec3 worldRotation() const;
        glm::vec3 worldScale() const;

        void setLocalPosition(glm::vec3 position);
        void setLocalRotation(glm::vec3 rotation);
        void setLocalScale(glm::vec3 scale);
        void setLocal(glm::vec3 position, glm::vec3 rotation);
        void setLocal(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

        void setWorldPosition(glm::vec3 position);
        void setWorldRotation(glm::vec3 rotation);
        void setWorld(glm::vec3 position, glm::vec3 rotation);

        glm::mat4x4 localToWorldMatrix();

        Transform();

    private:

        void rebuildMatrix();
        void rebuildMatrixIfNeeded();

        glm::mat4 getParentMatrix() const;

    private:

        glm::vec3 m_LocalPosition {0, 0, 0};
        glm::vec3 m_LocalRotation {0, 0, 0};
        glm::vec3 m_LocalScale {1, 1, 1};

        glm::mat4x4 m_LocalToWorld {1.f};

        bool m_IsDirty {false};

        Transform* m_Parent {nullptr};
        std::vector<Transform*> m_Children;
    };
}