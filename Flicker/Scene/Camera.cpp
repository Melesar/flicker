#include "Camera.hpp"
#include "Application/Input.hpp"

glm::mat4x4 Flicker::Camera::worldToClipMatrix() const
{
    glm::mat4x4 projMatrix = viewToClipMatrix();
    glm::mat4x4 viewMatrix = worldToViewMatrix();

    return projMatrix * viewMatrix;
}

glm::mat4x4 Flicker::Camera::worldToViewMatrix() const
{
    glm::vec3 cameraPos = worldPosition();
    return glm::lookAt(cameraPos, cameraPos + forward(), up());

}

glm::mat4x4 Flicker::Camera::viewToClipMatrix() const
{
    return glm::perspective(glm::radians(fov), (float) m_Width / m_Height, zNear, zFar);
}

void Flicker::Camera::processInput(float deltaTime)
{
    moveCamera(deltaTime);
    rotateCamera(deltaTime);

    m_LastMousePosition = Input::mousePosition();
}

void Flicker::Camera::moveCamera(float deltaTime)
{
    float offsetZ = 0, offsetX = 0;
    if (Input::isKeyDown(GLFW_KEY_W))
    {
        offsetZ += moveSpeed;
    }
    if (Input::isKeyDown(GLFW_KEY_S))
    {
        offsetZ -= moveSpeed;
    }
    if (Input::isKeyDown(GLFW_KEY_D))
    {
        offsetX -= moveSpeed;
    }
    if (Input::isKeyDown(GLFW_KEY_A))
    {
        offsetX += moveSpeed;
    }

    if (offsetX != 0 || offsetZ != 0)
    {
        glm::vec3 translation = offsetZ * forward() + offsetX * right();
        translateLocal(translation * deltaTime);
    }
}

void Flicker::Camera::rotateCamera(float deltaTime)
{
    if (!Input::isMouseButtonDown(1))
    {
        return;
    }

    glm::vec2 mouseDelta = Input::mousePosition() - m_LastMousePosition;
    mouseDelta /= glm::vec2(m_Width, m_Height);

    if (glm::length(mouseDelta) < 0.001f)
    {
        return;
    }

    glm::vec3 rotation = localRotation();
    rotation.x -= mouseDelta.y * mouseSensitivity;
    rotation.y -= mouseDelta.x * mouseSensitivity;
    setLocalRotation(rotation); 
}

Flicker::Camera::Camera(GLFWwindow* window)
{
    glfwGetWindowSize(window, &m_Width, &m_Height);
}

Flicker::Camera::~Camera()
{

}