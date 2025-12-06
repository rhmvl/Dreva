#include "World.hpp"

namespace dreva::world
{
World::World() = default;

Island& World::createIsland(int width, int height)
{
    auto island = std::make_unique<Island>(width, height, reg);
    islands.push_back(std::move(island));
    return *islands.back();
}

entt::registry& World::getRegistry() { return reg; }
}  // namespace dreva::world
