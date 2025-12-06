#include "Game.hpp"

namespace dreva::core
{

void WorldRenderTest(entt::registry& reg, float dt)
{
    (void) dt;

    auto& world = reg.ctx().get<world::World>();
    auto& render = reg.ctx().get<kine::RenderList>();
    const int tileSize = 32;

    for (auto& island : world.islands)
    {
        glm::vec2 pos = island->position;
        for (int y = 0; y <= island->height; ++y)
        {
            render.addLine(pos.x, pos.y + y * tileSize, pos.x + island->width * tileSize, pos.y + y * tileSize, 1.0f,
                           {255, 255, 255, 255});
        }
        for (int x = 0; x <= island->width; ++x)
        {
            render.addLine(pos.x + x * tileSize, pos.y, pos.x + x * tileSize, pos.y + island->height * tileSize, 1.0f,
                           {255, 255, 255, 255});
        }
    }
}

Game::Game(kine::Kine& kine) : engine(kine) {}

void Game::init()
{
    auto& sched = engine.getScheduler();
    world = std::make_shared<world::World>();

    engine.getRegistry().ctx().emplace<world::World&>(*world);
    world::Island& island = world->createIsland(10, 10);
    island.position = {40, 40};

    sched.addSystem("WorldRenderTest", WorldRenderTest);
}

void Game::update() {}
}  // namespace dreva::core
