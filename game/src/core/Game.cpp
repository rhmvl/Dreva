#include "Game.hpp"

using namespace dreva::engine;

void Test(entt::registry& reg, float dt)
{
    auto& list = reg.ctx().get<RenderList>();
    auto& resources = reg.ctx().get<ResourceManager>();

    Texture2D& tex = resources.getTexture("error");

    list.submit({.texture = &tex,
                 .position = glm::vec2(200, 300),
                 .pivot = glm::vec2(0, 0),
                 .rotation = 0,
                 .scale = 1,
                 .tint = WHITE});
}

void Game::init(Engine& engine)
{
    auto& sched = engine.getScheduler();

    sched.addSystem("Test", Test);
}
