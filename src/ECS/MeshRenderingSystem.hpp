#pragma once
#include "ECS_impl.hpp"

namespace Flicker
{
    class MeshRenderingSystem : public ecs::System<Settings, MeshRenderingSystem, MeshInstanceComponent, TransformComponent>
    {
    public:
        static void onUpdate(ecs::EntityHandle entity, EntityManager& entityManager, MeshInstanceComponent& meshInstance, TransformComponent& transform);
        MeshRenderingSystem(EntityManager& manager) : ecs::System<Settings, MeshRenderingSystem, MeshInstanceComponent, TransformComponent>(manager) { }
    };
}