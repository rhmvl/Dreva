#include "Game.hpp"
#define UNUSED(expr) (void)(expr)

using namespace kine;

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

    UNUSED(dt);
}

void Game::init(Kine& engine)
{
    auto& sched = engine.getScheduler();

    sched.addSystem("Test", Test);
}
