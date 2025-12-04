#pragma once
#include <raylib.h>
#include <memory>

#include "io/Input.hpp"
#include "rendering/Renderer.hpp"
#include "resources/ResourceManager.hpp"
#include "core/Scheduler.hpp"
#include "core/Time.hpp"

namespace dreva::engine
{

class Engine
{
   public:
    Engine();
    ~Engine();

    void init();
    void shutdown();

    void beginFrame();
    void update();
    void renderFrame();
    bool isRunning() const;

    float deltaTime() const { return time->dt; }
    entt::registry& getRegistry() { return reg; }

   private:
    bool running = false;

    std::unique_ptr<Time> time;
    std::unique_ptr<Input> input;
    std::unique_ptr<Scheduler> scheduler;
    std::shared_ptr<ResourceManager> resourceManager;
    std::shared_ptr<Renderer> renderer;

    entt::registry reg;
};

}  // namespace dreva::engine
