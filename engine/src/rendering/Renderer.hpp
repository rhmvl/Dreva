#pragma once
#include "../resources/ResourceManager.hpp"
#include "rendering/RenderList.hpp"

namespace kine
{

/**
 * @class Renderer
 * @brief Handles window creation, draw calls, and presentation.
 *
 * Uses Raylib for graphics; draws all RenderCommands submitted for the frame.
 */
class Renderer
{
   public:
    /**
     * @brief Constructs the renderer with resource and render list references.
     */
    explicit Renderer(ResourceManager* resourceManager, RenderList* list);
    ~Renderer() = default;

    /**
     * @brief Creates the game window and initializes renderer state.
     */
    void init(int width, int height, const char* title);

    /**
     * @brief Draws all queued rendering commands.
     */
    void render();

   private:
    ResourceManager* resources;  ///< Access to resource loading
    RenderList* list;            ///< List of render commands
};

}  // namespace kine
