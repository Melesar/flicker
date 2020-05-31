#pragma once

namespace ecs
{
    class FreeList
    {
    public:
        FreeList(void* buffer, size_t numElements, size_t elementSize);

        void* obtain();
        void free(void* ptr);

    private:
        FreeList* m_Next;
    };
}