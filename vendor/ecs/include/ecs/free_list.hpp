#pragma once

namespace ecs
{
    //A free-list pool allocator described here:
    //https://blog.molecular-matters.com/2012/09/17/memory-allocation-strategies-a-pool-allocator/
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