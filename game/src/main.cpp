#include "core/Game.hpp"

using namespace kine;
using namespace dreva;

int main(void)
{
    Kine engine;
    engine.init();

    core::Game game(engine);
    game.init();

    while (engine.isRunning())
    {
        engine.beginFrame();
        engine.update();
        engine.renderFrame();
    }

    engine.shutdown();
    return 0;
}
