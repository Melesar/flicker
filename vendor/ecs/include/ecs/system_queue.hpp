#pragma once 
#include "system.hpp"

namespace ecs
{
    template<typename TSettings, typename... TSystems>
    class SystemQueue
    {
        using SystemsList = mpl::TypeList<TSystems...>;

    public:
        void update(float deltaTime)
        {
            mpl::for_tuple(m_Systems, [deltaTime] (auto& ptr)
            {
                ptr->update(deltaTime);
            });
        }

        SystemQueue(EntityManager<TSettings>& manager) : m_Manager(manager) 
        {
            mpl::for_tuple(m_Systems, [this, &manager](auto& ptr)
            {
                using PtrType = typename std::remove_reference<decltype(ptr)>::type;
                using SystemType = typename PtrType::element_type;
                ptr = std::make_unique<SystemType>(manager);
            });
        }

    private:
        EntityManager<TSettings>& m_Manager;
        std::tuple<std::unique_ptr<TSystems...>> m_Systems;
    };
}