#include <iostream>
#include "MeshRenderingSystem.hpp"

void Flicker::MeshRenderingSystem::onUpdate(ecs::EntityHandle entity, Flicker::EntityManager& entityManager, Flicker::MeshInstanceComponent& meshInstance, Flicker::TransformComponent& transform)
{
    std::cout << "Mesh rendering update" << std::endl;
}