namespace Flicker
{
    struct Handle
    {
        uint16_t Index;
        uint16_t Generation;
    };

    struct ModelComponent
    {
        uint16_t StartMeshIndex;
        uint16_t MeshesCount;
    };
}