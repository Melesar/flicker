#include "Application.hpp"
#include "Data/Containers.hpp"

void Flicker::Application::run()
{
    Flicker::RenderingWorld* renderingWorld = Flicker::create_container<Flicker::RenderingWorld>();

    Flicker::free_container(renderingWorld);
}