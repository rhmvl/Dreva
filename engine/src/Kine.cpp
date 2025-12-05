#include "Kine.hpp"

#include <memory>
#include "raylib.h"

namespace kine
{

Kine::Kine() = default;
Kine::~Kine() = default;

void Kine::init()
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

void Kine::beginFrame()
{
    time->beginFrame();
    if (WindowShouldClose()) running = false;
}

void Kine::update()
{
    float dt = time->dt;

    scheduler->update(reg, dt);
    scheduler->fixedUpdate(reg, time->accumulator, time->fixedDt);
}

void Kine::renderFrame() { renderer->render(); }

bool Kine::isRunning() const { return running; }

void Kine::shutdown()
{
    resourceManager->shutdown();
    CloseWindow();
}
}  // namespace kine
