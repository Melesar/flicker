namespace Flicker
{
    struct WindowHandle;
    struct RenderingWorld;
    struct SceneHierarchy;

    class OpenGLRenderer
    {
    public:
        OpenGLRenderer(const WindowHandle& windowHandle, RenderingWorld& renderingWorld, SceneHierarchy& scene);
        ~OpenGLRenderer();

        void render();

    private:

        const WindowHandle& m_WindowHandle;
        RenderingWorld& m_RenderingWorld;
        SceneHierarchy& m_Scene;    
    };
}
