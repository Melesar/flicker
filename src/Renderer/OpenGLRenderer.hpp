#pragma once
#include <Data/Data.hpp>

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

        void loadShaders();

    private:

        const WindowHandle& m_WindowHandle;
        RenderingWorld& m_RenderingWorld;
        SceneHierarchy& m_Scene;    
        
        Shader m_LitShader;
    };
}
