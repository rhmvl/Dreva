#include "Chunk.hpp"
#include <cassert>

namespace dreva::world
{
Chunk::Chunk(Island& parent_, int startX_, int startY_, int width_, int height_)
    : parent(parent_), startX(startX_), startY(startY_), width(width_), height(height_)
{
}

Tile& Chunk::getTile(int localX, int localY)
{
    assert(localX >= 0 && localX < width);
    assert(localY >= 0 && localY < height);
    return parent.getTile(startX + localX, startY + localY);
}

const Tile& Chunk::getTile(int localX, int localY) const
{
    assert(localX >= 0 && localX < width);
    assert(localY >= 0 && localY < height);
    return parent.getTile(startX + localX, startY + localY);
}
}  // namespace dreva::world
