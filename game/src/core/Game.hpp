#pragma once
#include "Kine.hpp"
#include "world/World.hpp"

namespace dreva::core
{
class Game
{
   public:
    void init(kine::Kine& engine);

   private:
    world::World world;
};
}  // namespace dreva::core
