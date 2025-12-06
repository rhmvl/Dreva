#pragma once
#include <entt/entt.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include "Tile.hpp"

namespace dreva::world
{
class Island
{
   public:
    int width;
    int height;
    std::vector<Tile> tiles;
    glm::vec2 position;
    entt::registry& reg;

    Island(int width_, int height_, entt::registry& registry);

    Tile& getTile(int x, int y);
    const Tile& getTile(int x, int y) const { return tiles[y + width + x]; }
};

}  // namespace dreva::world
