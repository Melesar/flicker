namespace Flicker
{
    struct WindowHandle;
    struct RenderingWorld;
    struct Scene;

    class OpenGLRenderer
    {
    public:
        OpenGLRenderer(const WindowHandle& windowHandle, RenderingWorld& renderingWorld, Scene& scene);
        ~OpenGLRenderer();

        void render();

    private:

        const WindowHandle& m_WindowHandle;
        RenderingWorld& m_RenderingWorld;
        Scene& m_Scene;    
    };
}
