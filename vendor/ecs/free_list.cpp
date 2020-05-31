#include "ecs/free_list.hpp"

ecs::FreeList::FreeList(void *buffer, size_t numElements, size_t elementSize)
{
    union {
        void *asVoid;
        char *asChar;
        FreeList *asSelf;
    };

    asVoid = buffer;
    m_Next = asSelf;
    asChar += elementSize;

    FreeList *runner = m_Next;
    for (size_t i = 1; i < numElements; i++)
    {
        runner->m_Next = asSelf;
        runner = asSelf;
        asChar += elementSize;
    }

    runner->m_Next = nullptr;
}

void *ecs::FreeList::obtain()
{
    if (m_Next == nullptr)
    {
        return nullptr;
    }

    void *ptr = m_Next;
    m_Next = m_Next->m_Next;
    return ptr;
}

void ecs::FreeList::free(void *ptr)
{
    FreeList *head = static_cast<FreeList *>(ptr);
    head->m_Next = m_Next;
    m_Next = head;
}