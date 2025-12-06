#pragma once
#include <cstdint>
#include <entt/entt.hpp>

namespace dreva::world
{
struct Tile
{
    uint8_t terrainType = 0;
    uint8_t resourceType = 0;
    uint16_t buildingType = 0;
    entt::entity buildingEntity = entt::null;
};
}  // namespace dreva::world
