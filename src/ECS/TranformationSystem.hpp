#pragma once
#include "ECS_impl.hpp"

namespace Flicker
{
    class TransformationSystem : public ecs::System<Settings, TransformationSystem, TransformComponent>
    {
    public:
        static void onUpdate(ecs::EntityHandle entity, EntityManager& manager, TransformComponent& transform);
        TransformationSystem(EntityManager& manager) : ecs::System<Settings, TransformationSystem, TransformComponent>(manager) { }
    };
}
