#include "Application.hpp"
#include "Data/Components.hpp"
#include "Data/Containers.hpp"
#include "Data/Data.hpp"
#include "Assets/Assets.hpp"

void Flicker::Application::run()
{
    bootstrap();

    while(m_IsRunning)
    {
        mainLoop();
    }

    shutdown();
}

void Flicker::Application::bootstrap()
{
    m_IsRunning = false;
}

void Flicker::Application::mainLoop()
{

}

void Flicker::Application::shutdown()
{

}

Flicker::Application::Application()
{
    m_Hierarchy = Flicker::create_container<SceneHierarchy>();
    m_MeshesStorage = Flicker::create_container<MeshesStorage>();
    m_ModelsStorage = Flicker::create_container<ModelsStorage>();
    m_ShadersStorage = Flicker::create_container<ShadersStorage>();
}

Flicker::Application::~Application()
{
    Flicker::free_container(m_Hierarchy);
    Flicker::free_container(m_MeshesStorage);
    Flicker::free_container(m_ModelsStorage);
    Flicker::free_container(m_ShadersStorage);
}