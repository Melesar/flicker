#include "Input.hpp"

GLFWwindow* Flicker::Input::m_Window;
glm::vec2 Flicker::Input::m_LastMousePosition;

void Flicker::Input::update()
{
    
}

void Flicker::Input::onMousePositionChanged(GLFWwindow* window, double xPos, double yPos)
{
    m_LastMousePosition.x = static_cast<float>(xPos);
    m_LastMousePosition.y = static_cast<float>(yPos);
}

void Flicker::Input::init(GLFWwindow* window)
{
    m_Window = window;
    glfwSetCursorPosCallback(m_Window, onMousePositionChanged);
}

bool Flicker::Input::isKeyDown(int key)
{
    return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

bool Flicker::Input::isMouseButtonDown(int button)
{
    int buttonCode = button > 0 ? GLFW_MOUSE_BUTTON_RIGHT : GLFW_MOUSE_BUTTON_LEFT;
    return glfwGetMouseButton(m_Window, buttonCode) == GLFW_PRESS;
} 

glm::vec2 Flicker::Input::mousePosition()
{
    return m_LastMousePosition;
}