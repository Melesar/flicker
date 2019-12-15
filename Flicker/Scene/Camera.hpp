    #pragma once
#include "Node.hpp"

namespace Flicker
{
    class Camera : public Node
    {
    public:
        float fov {60};
        float zNear {0.1f}, zFar {100.f};

    public:

        glm::mat4x4 worldToClipMatrix() const;

        Camera(GLFWwindow* window);
        virtual ~Camera();

    private:

        int m_Width;
        int m_Height;
    };
}