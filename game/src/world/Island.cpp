#include "Island.hpp"
#include <cassert>

namespace dreva::world
{

Island::Island(int width_, int height_, entt::registry& reg_)
    : width(width_), height(height_), tiles(width_ * height_), position(0.0f, 0.0f), reg(reg_)
{
}
Tile& Island::getTile(int x, int y)
{
    assert(x >= 0 && x < width);
    assert(y >= 0 && y < height);
    return tiles[y * width + x];
}

}  // namespace dreva::world
