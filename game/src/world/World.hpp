#pragma once
#include <entt/entt.hpp>
#include <memory>
#include <vector>
#include "Island.hpp"

namespace dreva::world
{
class World
{
   public:
    std::vector<std::unique_ptr<Island>> islands;

    World();

    Island& createIsland(int width, int height);

    entt::registry& getRegistry();

   private:
    entt::registry reg;
};
}  // namespace dreva::world
