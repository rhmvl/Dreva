#include "core/Game.hpp"

using namespace kine;

int main(void)
{
    Kine engine;
    engine.init();

    Game game;
    game.init(engine);

    while (engine.isRunning())
    {
        engine.beginFrame();
        engine.update();
        engine.renderFrame();
    }

    engine.shutdown();
    return 0;
}
