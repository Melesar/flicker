#pragma once

namespace Flicker
{
    struct Handle
    {
        uint16_t Index;
        uint16_t Generation;
    };

    struct TransformHandle : public Handle { };
    struct MeshHandle : public Handle { };

    struct ModelComponent
    {
        uint16_t StartMeshIndex;
        uint16_t MeshesCount;
    };

    struct ModelEntity
    {
        TransformHandle Transform;
        ModelComponent Model;
    };
    
    struct WindowHandle
    {
        uint16_t Width;
        uint16_t Height;
    };
}