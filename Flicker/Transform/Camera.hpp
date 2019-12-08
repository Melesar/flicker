#pragma once
#include "Transform.hpp"

namespace Flicker
{
    class Camera
    {
    public:
        float fov {60};
        float zNear {0.1f}, zFar {100.f};
        //Transform transform;

    public:

        glm::mat4x4 worldToClipMatrix() const;

        Camera(GLFWwindow* window);
        virtual ~Camera();

    private:

        int m_Width;
        int m_Height;
    };
}