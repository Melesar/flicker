#pragma once

namespace Flicker
{
    struct Transform
    {
        glm::vec3 position {0, 0, 0};
        glm::vec3 rotation {0, 0, 0};
        glm::vec3 scale {1, 1, 1};

        void setParent(Transform& parent);
        void addChild(Transform& child);

        Transform& getParent();
        Transform& getChild(int index);
        int childCount() const;  

        glm::mat4x4 localToWorldMatrix() const;

        Transform();

    private:

        Transform* parent {nullptr};
        std::vector<Transform> children;
    };
}