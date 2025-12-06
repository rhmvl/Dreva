#pragma once
#include <glm/vec4.hpp>
#include <vector>

#include "RenderCommand.hpp"

namespace kine
{

class ResourceManager;

/**
 * @struct RenderBatch
 * @brief A collection of drawing commands that share the same texture.
 *
 * The Renderer can draw each batch in one go, reducing texture switches.
 * - If texturePtr == nullptr, batch contains primitive shapes (rect/line/circle)
 * - If non-null, batch contains sprite commands sharing that texture
 */
struct RenderBatch
{
    /**
     * @brief Pointer identifying which texture this batch uses.
     *
     * The pointer is used only for grouping and comparison.
     * It is NOT owned by the batch.
     */
    void* texturePtr{nullptr};

    /**
     * @brief All commands that belong to this batch.
     */
    std::vector<const RenderCommand*> commands;
};

/**
 * @class RenderBatcher
 * @brief Groups render commands into texture-based batches.
 *
 * Responsibilities:
 *  - Sort submitted RenderCommands by draw layer (stable order).
 *  - Group sprite commands by texture to reduce draw calls.
 *  - Group shape commands into a special “no texture” batch.
 */
class RenderBatcher
{
   public:
    /**
     * @brief Constructs the batcher.
     * @param resources Pointer to resource manager used for texture lookup.
     */
    RenderBatcher(ResourceManager* resources);

    /**
     * @brief Builds sorted and batched render groups from raw commands.
     *
     * @param commands A list of render commands for the current frame.
     *
     * Produces:
     *  - sorted: list of sorted raw command pointers
     *  - batches: grouped commands, one batch per texture
     */
    void buildBatches(const std::vector<RenderCommand>& commands);

    /**
     * @brief Provides read-only access to the generated batches.
     */
    const std::vector<RenderBatch>& getBatches() const;

   private:
    ResourceManager* resourceManager{nullptr};  ///< Texture lookup source

    /**
     * @brief Temporary sorted command list (pointers only).
     */
    std::vector<const RenderCommand*> sorted;

    /**
     * @brief Final grouped render batches.
     */
    std::vector<RenderBatch> batches;
};

}  // namespace kine
