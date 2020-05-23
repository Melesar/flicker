
class GLFWwindow;

namespace Flicker 
{
    class Application
    {
    public:
        Application();
        ~Application();

        void run();

    private:
        bool m_IsRunning;
        GLFWwindow* m_WindowHandle;
    };
}