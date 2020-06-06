#pragma once
#include <ecs/system_queue.hpp>

namespace Flicker
{
    struct MeshInstanceComponent
    {
        size_t MeshHandle;
        size_t MaterialHandle;
    };

    struct TransformComponent
    {
        size_t ParentIndex;
        glm::mat4 LocalTransform;
        glm::mat4 GlobalTransfrom;
    };  

    using Settings = ecs::Settings<MeshInstanceComponent, TransformComponent>;
    using EntityManager = ecs::EntityManager<Settings>;

    class TransformationSystem;
    class MeshRenderingSystem;

    using SystemQueue = ecs::SystemQueue<Settings, TransformationSystem, MeshRenderingSystem>;
}

