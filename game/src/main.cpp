#include <Engine.hpp>

int main()
{
    dreva::engine::Engine engine;
    engine.init();

    while (engine.isRunning())
    {
        engine.beginFrame();  // ticks Time, Input, etc
        engine.update();
        // game.update(engine.getRegistry(), engine.deltaTime());
        engine.renderFrame();  // renderer->render()
    }

    engine.shutdown();
    return 0;
}
