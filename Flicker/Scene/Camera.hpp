    #pragma once
#include "Node.hpp"

namespace Flicker
{
    class Camera : public Node
    {
    public:
        float fov {60};
        float zNear {0.1f}, zFar {100.f};
        float moveSpeed {10.f};
        float mouseSensitivity {10.f};

    public:

        glm::mat4x4 worldToClipMatrix() const;
        void processInput(float deltaTime);

        Camera(GLFWwindow* window);
        virtual ~Camera();

    private:

        void moveCamera(float deltaTime);
        void rotateCamera(float deltaTime);

    private:

        int m_Width;
        int m_Height;

        glm::vec2 m_LastMousePosition;
    };
}