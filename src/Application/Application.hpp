
class GLFWwindow;

namespace Flicker 
{
    class Application
    {
    public:
        Application();
        ~Application();
        Application(const Application& app) = delete;

        void run();

    private:
        bool m_IsRunning;
        GLFWwindow* m_WindowHandle;
    };
}