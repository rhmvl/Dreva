#pragma once
#include <cstdint>
#include <entt/entt.hpp>
#include <string>
#include "Tile.hpp"

namespace dreva::world
{
struct Island;
struct BuildingType
{
    uint16_t id;
    std::string name;
    bool solid = false;
    bool generatesPower = false;
    int width = 1;
    int height = 1;

    // Optional update logic for systems
    void (*update)(Tile&, Island&, entt::registry&, float dt) = nullptr;
};
}  // namespace dreva::world
