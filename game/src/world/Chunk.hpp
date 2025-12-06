#pragma once
#include <span>
#include "Island.hpp"

namespace dreva::world
{
class Chunk
{
   public:
    Chunk(Island& parent_, int startX_, int startY_, int width_, int height_);

    Tile& getTile(int localX, int localY);
    const Tile& getTile(int localX, int localY) const;

   private:
    Island& parent;
    int startX;
    int startY;
    int width;
    int height;
    std::span<Tile> tiles;
};
}  // namespace dreva::world
