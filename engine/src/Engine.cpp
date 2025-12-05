#include "Engine.hpp"

#include <memory>
#include "raylib.h"

namespace dreva::engine
{

Engine::Engine() = default;
Engine::~Engine() = default;

void Engine::init()
{
    time = std::make_unique<Time>();
    input = std::make_unique<Input>();
    scheduler = std::make_unique<Scheduler>();
    resourceManager = std::make_shared<ResourceManager>();
    renderList = std::make_unique<RenderList>();
    renderer = std::make_unique<Renderer>(resourceManager.get(), renderList.get());

    reg.ctx().emplace<RenderList&>(*renderList);
    reg.ctx().emplace<ResourceManager&>(*resourceManager);

    renderer->init(1280, 720, "Dreva");
    resourceManager->init();
    running = true;
}

void Engine::beginFrame()
{
    time->beginFrame();
    if (WindowShouldClose()) running = false;
}

void Engine::update()
{
    float dt = time->dt;

    scheduler->update(reg, dt);
    scheduler->fixedUpdate(reg, time->accumulator, time->fixedDt);
}

void Engine::renderFrame() { renderer->render(); }

bool Engine::isRunning() const { return running; }

void Engine::shutdown()
{
    resourceManager->shutdown();
    CloseWindow();
}
}  // namespace dreva::engine
