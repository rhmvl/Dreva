#include <Engine.hpp>
#include "core/Game.hpp"

using namespace dreva::engine;

int main(void)
{
    Engine engine;
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
