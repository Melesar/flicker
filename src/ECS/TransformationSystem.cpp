#include "pch.hpp"
#include "TranformationSystem.hpp"

void Flicker::TransformationSystem::onUpdate(ecs::EntityHandle entity, Flicker::EntityManager& manager, TransformComponent& transform)
{
    std::cout << "Transformation update" << std::endl;
}