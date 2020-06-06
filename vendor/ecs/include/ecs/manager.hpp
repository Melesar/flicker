#pragma once
#include "mpl.hpp"
#include "free_list.hpp"
#include <bitset>
#include <vector>
#include <memory>
#include <cassert>

namespace ecs 
{
    struct Entity
    {
        size_t index;
        size_t generation;
    };

    typedef const size_t* EntityHandle;

    template<typename... TComponents>
    struct Settings
    {
        using ComponentList = mpl::TypeList<TComponents...>;

        static constexpr int numComponents() { return ComponentList::size; }
        template<typename TComponent>
        static constexpr int componentId() { return mpl::IndexOf<TComponent, ComponentList>::value; }
        template<typename TComponent>
        static constexpr bool isComponent() { return mpl::Contains<TComponent, ComponentList>::value; }

        using Bitset = std::bitset<numComponents()>;
    };

    template<typename TSettings>
    class EntityManager
    {
        using Settings = TSettings;
        using Bitset = typename Settings::Bitset;
        using Components = typename Settings::ComponentList;
        template<typename... TArgs>
        using TupleOfVectors = mpl::Tuple<std::vector<TArgs>...>;
        using ComponentStorage = mpl::Rename<TupleOfVectors, Components>;

    public:

        EntityManager()
        {
            grow(100);
            std::fill(m_Generations.begin(), m_Generations.end(), 0);
        }

        EntityHandle createEntity()
        {
            growIfNeeded();

            Entity& e = m_Entities[m_NextEntityIndex];
            e.index = m_NextEntityIndex;
            e.generation = m_Generations[m_NextEntityIndex];
            m_Bitsets[m_NextEntityIndex].reset();

            size_t* handle = static_cast<size_t*>(m_Lookup->obtain());
            *handle = m_NextEntityIndex;
            m_ArrayToLookup[m_NextEntityIndex] = handle;

            m_NextEntityIndex++;
            m_isDirty = true;

            return handle;
        }

        void deleteEntity(EntityHandle e)
        {
            m_isDirty = true;
            m_Generations[*e] = m_Entities[*e].generation + 1;
            m_Lookup->free(m_ArrayToLookup[*e]);
        }

        template<typename T>
        T& addComponent(EntityHandle e, const T&& component)
        {
            assertIsComponent<T>();
            assert(isEntityExists(e));

            T& c = getComponent<T>(e);
            c = component;
            m_Bitsets[*e].set(Settings::componentId<T>());

            return c; 
        }

        template<typename T>
        T& getComponent(EntityHandle e)
        {
            assertIsComponent<T>();
            assert(isEntityExists(e));
            return std::get<std::vector<T>>(m_ComponentsStorage)[*e];
        }

        template<typename T>
        const T& getComponent(EntityHandle e) const
        {
            assert(isEntityExists(e));
            return getComponent<T>(e);
        }

        template<typename T>
        bool hasComponent(EntityHandle e) const
        {
            assertIsComponent<T>();
            assert(isEntityExists(e));

            return m_Bitsets[*e][Settings::componentId<T>()];
        }

        bool isEntityExists(EntityHandle e) const
        {
            return *e < m_Capacity && m_Generations[*e] == m_Entities[*e].generation;
        }

        void refresh()
        {
            if (!m_isDirty)
            {
                return;
            }

            if (m_NextEntityIndex == 0)
            {
                m_CurrentEntityIndex = 0;
                m_isDirty = false;
                return;
            }

            m_CurrentEntityIndex = m_NextEntityIndex = refreshImpl();
            m_isDirty = false;
        }

        template<typename TFunc>
        void forEntities(TFunc&& func)
        {
            for (size_t i = 0; i < m_CurrentEntityIndex; i++)
            {
                func(m_ArrayToLookup[i]);
            }
        }

        template<typename TFunc>
        void forEntities(Bitset signature, TFunc&& func)
        {
            for (size_t i = 0; i < m_CurrentEntityIndex; i++)
            {
                if ((signature & m_Bitsets[i]) == signature)
                {
                    func(m_ArrayToLookup[i]);
                }
            }
        }

        EntityManager(const EntityManager& manger) = delete;
        EntityManager(EntityManager&& manager) :
            m_CurrentEntityIndex(manager.m_CurrentEntityIndex),
            m_NextEntityIndex(manager.m_NextEntityIndex),
            m_Capacity(manager.m_Capacity),
            m_isDirty(manager.m_isDirty),
            m_LookupMemory(manager.m_LookupMemory),
            m_Lookup(std::move(manager.m_Lookup)),
            m_Entities(std::move(manager.m_Entities)),
            m_Generations(std::move(manager.m_Generations)),
            m_Bitsets(std::move(manager.m_Bitsets)),
            m_ArrayToLookup(std::move(manager.m_ArrayToLookup)),
            m_ComponentsStorage(std::move(manager.m_ComponentsStorage))
        {
            manager.m_LookupMemory = nullptr;
        }

    private:

        template<typename T>
        static constexpr void assertIsComponent()
        {
            static_assert(Settings::isComponent<T>());
        }

        bool isEntityExists(size_t index) const
        {
            return m_Generations[index] == m_Entities[index].generation;
        }

        void growIfNeeded()
        {
            if (m_NextEntityIndex >= m_Capacity)
            {
                grow(m_Capacity << 1);
            }
        }

        void grow(size_t capacity)
        {
            assert(capacity > m_Capacity);

            updateLookup(capacity);

            m_Capacity = capacity;
            m_Entities.resize(m_Capacity);
            m_Generations.resize(m_Capacity);
            m_Bitsets.resize(m_Capacity);
            m_ArrayToLookup.resize(m_Capacity);

            mpl::for_tuple(m_ComponentsStorage, [this](auto& components)
            {
                components.resize(m_Capacity);
            });
        }

        size_t refreshImpl()
        {
            size_t aliveIndex {m_NextEntityIndex - 1};
            size_t deadIndex {0};

            while (true)
            {
                for(; true; deadIndex++)
                {
                    if (deadIndex > aliveIndex) return deadIndex;
                    if (!isEntityExists(deadIndex)) break;
                }

                for (; true; aliveIndex--)
                {
                    if (aliveIndex <= deadIndex) return deadIndex;
                    if (isEntityExists(aliveIndex)) break;
                }
                
                assert(isEntityExists(aliveIndex));
                assert(!isEntityExists(deadIndex));

                *m_ArrayToLookup[aliveIndex] = deadIndex;
                *m_ArrayToLookup[deadIndex] = aliveIndex;
                m_Entities[aliveIndex].index = deadIndex;
                m_Entities[deadIndex].index = aliveIndex;

                std::swap(m_Entities[aliveIndex], m_Entities[deadIndex]);
                std::swap(m_Generations[aliveIndex], m_Generations[deadIndex]);
                std::swap(m_Bitsets[aliveIndex], m_Bitsets[deadIndex]);
                std::swap(m_ArrayToLookup[aliveIndex], m_ArrayToLookup[deadIndex]);

                mpl::for_tuple(m_ComponentsStorage, [deadIndex, aliveIndex](auto& components)
                {
                    std::swap(components[aliveIndex], components[deadIndex]);
                });

                deadIndex++;
                aliveIndex--;
            }
        }

        void updateLookup(size_t newCapacity)
        {
            size_t* lookup = new size_t[newCapacity];
            if (m_LookupMemory != nullptr)
            {
                std::memcpy(lookup, m_LookupMemory, m_Capacity);
                delete m_LookupMemory;
            }

            m_LookupMemory = lookup;
            if (m_Lookup != nullptr)
            {
                m_Lookup.reset();
            }
            m_Lookup = std::make_unique<FreeList>(m_LookupMemory, newCapacity, sizeof(size_t));
        }

    private:
        size_t m_CurrentEntityIndex {0};
        size_t m_NextEntityIndex {0};
        size_t m_Capacity {0};
        bool m_isDirty {false};

        size_t* m_LookupMemory{nullptr};
        std::unique_ptr<FreeList> m_Lookup;
        std::vector<Entity> m_Entities;
        std::vector<size_t> m_Generations;
        std::vector<Bitset> m_Bitsets;
        std::vector<size_t*> m_ArrayToLookup;

        ComponentStorage m_ComponentsStorage;
    };
}