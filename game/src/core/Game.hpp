#pragma once
#include <memory>
#include "Kine.hpp"
#include "world/World.hpp"

namespace dreva::core
{
class Game
{
   public:
    Game(kine::Kine& kine);

    void init();
    void update();

   private:
    kine::Kine& engine;
    std::shared_ptr<world::World> world;
};
}  // namespace dreva::core
