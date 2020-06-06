#pragma once 
#include "system.hpp"

namespace ecs
{
    template<typename TSettings, typename... TSystems>
    class SystemQueue
    {
    public:
        void update(float deltaTime)
        {
            mpl::for_tuple(m_Systems, [this, deltaTime] (auto& ptr)
            {
                ptr->update(deltaTime);
                m_Manager.refresh();
            });
        }

        SystemQueue(EntityManager<TSettings>& manager) :
            m_Manager(manager),
            m_Systems(std::make_tuple(std::move(std::make_unique<TSystems>(manager))...))
        {  }

    private:
        EntityManager<TSettings>& m_Manager;
        std::tuple<std::unique_ptr<TSystems>...> m_Systems;
    };
}