namespace Flicker 
{
    struct SceneHierarchy;
    struct MeshesStorage;
    struct ModelsStorage;
    struct ShadersStorage;

    class Application
    {
    public:
        void run();

        Application();
        ~Application();

        Application(const Application& app) = delete;

    private: 

        void bootstrap();
        void mainLoop();
        void shutdown();

    private:

        bool m_IsRunning;

        SceneHierarchy* m_Hierarchy;
        MeshesStorage* m_MeshesStorage;
        ModelsStorage* m_ModelsStorage;
        ShadersStorage* m_ShadersStorage;
    };
}