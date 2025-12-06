#pragma once
#include <raylib.h>
#include <memory>

#include "core/Scheduler.hpp"
#include "core/Time.hpp"
#include "io/Input.hpp"
#include "rendering/RenderBatcher.hpp"
#include "rendering/RenderList.hpp"
#include "rendering/Renderer.hpp"
#include "resources/ResourceManager.hpp"

namespace kine
{

/**
 * @class Kine
 * @brief Central engine class orchestrating systems, rendering, input, and ECS.
 *
 * Kine owns the main ECS registry, scheduler, resource manager, and renderer.
 * It provides the main game loop interface.
 */
class Kine
{
   public:
    Kine();
    ~Kine();

    /**
     * @brief Initializes all engine subsystems.
     */
    void init();

    /**
     * @brief Cleans up engine resources.
     */
    void shutdown();

    /**
     * @brief Called at the beginning of each frame.
     *
     * Updates time, processes window events, checks for close request.
     */
    void beginFrame();

    /**
     * @brief Updates all registered systems (variable and fixed).
     */
    void update();

    /**
     * @brief Renders everything for the current frame.
     */
    void renderFrame();

    /**
     * @brief Returns true while the engine should continue running.
     */
    bool isRunning() const;

    /**
     * @brief Gets the delta time for the current frame.
     */
    float deltaTime() const { return time->dt; }

    /**
     * @brief Access to the ECS registry.
     */
    entt::registry& getRegistry() { return reg; }

    /**
     * @brief Access to the Scheduler.
     */
    Scheduler& getScheduler() { return *scheduler; }

    /**
     * @brief Access to the input
     */
    Input& getInput() { return *input; }

   private:
    bool running = false;  ///< Whether the engine is active

    std::unique_ptr<Time> time;            ///< Time system
    std::unique_ptr<Input> input;          ///< Input system
    std::unique_ptr<Scheduler> scheduler;  ///< System scheduler

    std::shared_ptr<ResourceManager> resourceManager;  ///< Resource loader/cache
    std::shared_ptr<Renderer> renderer;                ///< Rendering backend
    std::shared_ptr<RenderBatcher> renderBatcher;      ///< Rendering backend
    std::shared_ptr<RenderList> renderList;            ///< List of render commands

    entt::registry reg;  ///< Main ECS registry
};

}  // namespace kine
