#pragma once
#include "../resources/ResourceManager.hpp"
#include "rendering/RenderBatcher.hpp"
#include "rendering/RenderList.hpp"

namespace kine
{

/**
 * @enum ScalingMode
 * @brief Defines how the virtual or game resolution scales to the actual window.
 */
enum class ScalingMode : uint8_t
{
    PixelPerfectInteger,
    FreeScale,
    LetterboxedAuto
};

/**
 * @class Renderer
 * @brief Core rendering system handling window, scaling, and drawing.
 *
 * Responsibilities:
 *  - Manage window and virtual resolution
 *  - Draw RenderCommands directly or via RenderBatcher
 *  - Support multiple scaling modes
 *  - Optional debug overlays
 *
 * Uses Raylib for low-level drawing operations.
 */
class Renderer
{
   public:
    /**
     * @brief Constructs the renderer with references to resource systems.
     */
    explicit Renderer(ResourceManager* resourceManager, RenderList* list, RenderBatcher* batch);
    ~Renderer();

    /**
     * @brief Creates the game window and initializes renderer state.
     */
    void init(int width, int height, const char* title);

    /**
     * @brief Properly shuts down the renderer and cleans up resources.
     */
    void shutdown();

    /**
     * @brief Draws all queued rendering commands.
     */
    void render();

    /**
     * @brief Begins a new frame (prepares render targets).
     */
    void beginFrame();

    /**
     * @brief Ends the frame (presents the final image to screen).
     */
    void endFrame();

    /**
     * @brief Enables a virtual resolution for rendering.
     *
     * Draw commands are rendered to an off-screen target, then scaled to
     * the window according to the scaling mode.
     *
     * @param width Virtual width in pixels.
     * @param height Virtual height in pixels.
     */
    void setVirtualResolution(int width, int height);

    /**
     * @brief Disables virtual resolution and draws directly to the window.
     */
    void disableVirtualResolution();

    /**
     * @brief Checks if virtual resolution is currently enabled.
     */
    bool usingVirtualResolution() const { return virtualEnabled; }

    // Scaling mode
    void setScalingMode(ScalingMode mode) { scalingMode = mode; }
    ScalingMode getScalingMode() const { return scalingMode; }

    /**
     * TODO
     * @brief Draws an overlay showing debug information (FPS, batch stats, etc.).
     */
    void drawDebugOverlay();

   private:
    ResourceManager* resources;  ///< Access to textures and assets
    RenderList* list;            ///< Current frame's draw commands
    RenderBatcher* batcher;      ///< Optional sprite batcher

    // Virtual render target
    bool virtualEnabled{false};       ///< True if using off-screen target
    int virtualWidth{0};              ///< Width of virtual render target
    int virtualHeight{0};             ///< Height of virtual render target
    RenderTexture2D virtualTarget{};  ///< Raylib off-screen texture

    // Scaling mode
    ScalingMode scalingMode{ScalingMode::LetterboxedAuto};

    // Cached scaling parameters
    float finalScaleX{1.0f};
    float finalScaleY{1.0f};
    int finalOffsetX{0};
    int finalOffsetY{0};

    /**
     * @brief Draws commands using the batching system if available.
     */
    void drawBatches();

    /**
     * @brief Draws all commands directly to the window without batching.
     */
    void drawBatchesDirect();

    /**
     * @brief Draws all commands to the virtual render target, then scales to window.
     */
    void drawBatchesVirtual();

    /**
     * @brief Computes scaling factors and offsets for virtual resolution.
     * @param windowW Actual window width
     * @param windowH Actual window height
     */
    void computeVirtualScaling(int windowW, int windowH);

    // Primitive draw helpers
    void drawSprite(const RenderCommand* cmd, const Texture2D* tex);
    void drawRect(const RenderCommand* cmd);
    void drawCircle(const RenderCommand* cmd);
    void drawLine(const RenderCommand* cmd);
};

}  // namespace kine
