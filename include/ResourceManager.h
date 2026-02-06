#pragma once
#include <map>
#include "Resource.h"

/// Process-wide resource pool used by building simulation.
class ResourceManager
{
public:
    ResourceManager(const ResourceManager &) = delete;
    ResourceManager &operator=(const ResourceManager &) = delete;
    ResourceManager(ResourceManager &&) = delete;
    ResourceManager &operator=(ResourceManager &&) = delete;

    [[nodiscard]] static ResourceManager &Instance()
    {
        static ResourceManager inst;
        return inst;
    }

    void Add(ResourceType type, float amount)
    {
        m_resources[type] += amount;
    }

    /// Tries to consume amount and returns false if insufficient.
    [[nodiscard]] bool Consume(ResourceType type, float amount)
    {
        auto &stored = m_resources[type];
        if (stored >= amount)
        {
            stored -= amount;
            return true;
        }
        return false;
    }

    /// Returns current amount of a resource.
    [[nodiscard]] float Get(ResourceType type) const
    {
        auto it = m_resources.find(type);
        return it == m_resources.end() ? 0.0f : it->second;
    }

private:
    ResourceManager() = default;

    std::map<ResourceType, float> m_resources;
};
