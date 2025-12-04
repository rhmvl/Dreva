#include "Scheduler.hpp"

namespace dreva::engine
{

bool Scheduler::addSystem(std::string name, SystemFunc func)
{
    systems.emplace(std::move(name), std::move(func));
    dirty = true;
    return true;
}

bool Scheduler::addDependency(const std::string& before, const std::string& after)
{
    edges[before].push_back(after);
    dirty = true;
    return true;
}

bool Scheduler::visit(const std::string& name)
{
    if (perm[name]) return true;
    if (temp[name])
    {
        hasCycle = true;
        return false;
    }

    temp[name] = true;

    for (const auto& dep : edges[name])
    {
        if (!visit(dep)) return false;
    }

    temp[name] = false;
    perm[name] = true;
    sorted.push_back(name);

    return true;
}

bool Scheduler::rebuildOrder()
{
    sorted.clear();
    perm.clear();
    temp.clear();
    hasCycle = false;

    for (auto& [name, _] : systems)
    {
        if (!perm[name] && !visit(name))
        {
            sorted.clear();
            return false;  // cycle error
        }
    }

    dirty = false;
    return true;
}

void Scheduler::update(entt::registry& reg, float dt)
{
    if (dirty)
    {
        if (!rebuildOrder()) return;  // safe fail: skip update
    }

    for (auto& name : sorted)
    {
        systems[name](reg, dt);
    }
}

void Scheduler::fixedUpdate(entt::registry& reg, float& accumulator, float fixedDt)
{
    if (dirty)
    {
        if (!rebuildOrder()) return;
    }

    while (accumulator >= fixedDt)
    {
        for (auto& name : sorted)
        {
            systems[name](reg, fixedDt);
        }
        accumulator -= fixedDt;
    }
}

}  // namespace dreva::engine
