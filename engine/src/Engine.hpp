#pragma once
#include <raylib.h>
#include <memory>

#include "core/Scheduler.hpp"
#include "core/Time.hpp"
#include "io/Input.hpp"
#include "rendering/RenderList.hpp"
#include "rendering/Renderer.hpp"
#include "resources/ResourceManager.hpp"

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
    Scheduler& getScheduler() { return *scheduler; }

   private:
    bool running = false;

    std::unique_ptr<Time> time;
    std::unique_ptr<Input> input;
    std::unique_ptr<Scheduler> scheduler;

    std::shared_ptr<ResourceManager> resourceManager;
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<RenderList> renderList;

    entt::registry reg;
};

}  // namespace dreva::engine
