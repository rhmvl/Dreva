#include "Game.hpp"
#include <glm/ext/vector_int2.hpp>
#define UNUSED(expr) (void) (expr)

using namespace kine;

std::array<float, 4> toColor(Color c)
{
    std::array<float, 4> color;

    color[0] = static_cast<float>(c.r) / 255.0f;  // Red
    color[1] = static_cast<float>(c.g) / 255.0f;  // Green
    color[2] = static_cast<float>(c.b) / 255.0f;  // Blue
    color[3] = static_cast<float>(c.a) / 255.0f;  // Alpha

    return color;
}

namespace dreva::core
{
void Test(entt::registry& reg, float dt)
{
    auto& list = reg.ctx().get<RenderList>();

    list.addSprite("error", 100, 100, 0, 0, 0, 1);
    list.addCircle(300, 300, 20, toColor(WHITE));
    list.addLine(1, 1, 120, 120, 10, toColor(WHITE));
    list.addRect(320, 20, 100, 130, toColor(WHITE));

    UNUSED(dt);
}

void Game::init(Kine& engine)
{
    auto& sched = engine.getScheduler();
    engine.getRegistry().ctx().emplace<world::World*>(&world);

    world.getTile(glm::ivec2(100, 200));

    sched.addSystem("Test", Test);
}
}  // namespace dreva::core
