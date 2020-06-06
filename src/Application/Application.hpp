#include <Assets/AssetsStorage.hpp>

struct GLFWwindow;

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

    private:
        bool m_IsRunning;
        GLFWwindow* m_WindowHandle;
        AssetsStorage m_AssetsStorage;
    };
}