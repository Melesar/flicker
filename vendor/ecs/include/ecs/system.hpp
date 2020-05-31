#pragma once
#include "manager.hpp"

namespace ecs
{
    template<typename TSettings, typename TSystem, typename... TComponents>
    class System
    {
    protected:
        using Settings = TSettings;
        using AllComponents = typename Settings::ComponentList;
        using Bitset = typename Settings::Bitset;
        using SystemComponents = mpl::TypeList<TComponents...>;
        using EntityManager = EntityManager<Settings>;
    
    public:
    
        System(EntityManager& manager) : m_Manager(manager)
        {
            initSignature();
        }

        void update(float deltaTime)
        {
            m_Manager.forEntities(m_Signature, [this](EntityHandle entity)
            {
                TSystem::onUpdate(entity, m_Manager, m_Manager.getComponent<TComponents>(entity)...);
            });
        }

    private:

        void initSignature()
        {
            mpl::for_types<SystemComponents>([this](auto t)
            {
                m_Signature[Settings::componentId<decltype(t)>()] = true;
            });
        }

    private:
        Bitset m_Signature;
        EntityManager& m_Manager;
    };
}
    