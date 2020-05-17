#pragma once

namespace Flicker
{
    class Input
    {
    public:

        static void init(GLFWwindow* window);
        static bool isInitialized();
        static void update();

        static bool isKeyDown(int key);
        static bool isMouseButtonDown(int button);
        static glm::vec2 mousePosition();

    private:

        static void onMousePositionChanged(GLFWwindow* window, double xPos, double yPos);

        Input();
        ~Input();

    private:

        static glm::vec2 m_LastMousePosition;
        static GLFWwindow* m_Window;
    };
}