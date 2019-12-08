#include "Camera.hpp"

glm::mat4x4 Flicker::Camera::worldToClipMatrix() const
{
    glm::mat4x4 projMatrix = glm::perspective(glm::radians(fov), (float) m_Width / m_Height, zNear, zFar);
    glm::mat4x4 viewMatrix = glm::lookAt({0, 0, 0}, glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

    return projMatrix * viewMatrix;
}

Flicker::Camera::Camera(GLFWwindow* window)
{
    glfwGetWindowSize(window, &m_Width, &m_Height);
}

Flicker::Camera::~Camera()
{

}