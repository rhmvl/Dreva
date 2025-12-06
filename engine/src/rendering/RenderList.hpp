#pragma once
#include <vector>
#include "RenderCommand.hpp"

namespace kine
{

/**
 * @class RenderList
 * @brief Stores frame-specific render commands.
 *
 * Systems submit draw commands during update; Renderer consumes them during
 * rendering. The list is cleared every frame.
 */
class RenderList
{
   public:
    /**
     * @brief Preallocates command storage for efficiency.
     */
    RenderList();

    /**
     * @brief Returns all stored commands.
     */
    const std::vector<RenderCommand>& get() const { return commands; }

    /**
     * @brief Removes all commands after rendering.
     */
    void clear() { commands.clear(); }

    /**
     * @brief Appends a sprite drawing command.
     */
    void addSprite(const std::string& textureName, float x, float y, float rotation, float pivotX, float pivotY,
                   float scale = 1, int32_t layer = 1);
    /**
     * @brief Appends a filled rectangle draw command.
     */
    void addRect(float x, float y, float w, float h, std::array<float, 4> color, float scale = 1, int32_t layer = 1);

    /**
     * @brief Appends a circle draw command.
     */
    void addCircle(float x, float y, float radius, std::array<float, 4> color, float scale = 1, int32_t layer = 1);

    /**
     * @brief Appends a line draw command.
     */
    void addLine(float x1, float y1, float x2, float y2, float thickness, std::array<float, 4> color, float scale = 1,
                 int32_t layer = 1);

   private:
    std::vector<RenderCommand> commands;  ///< All draw commands for current frame
};

}  // namespace kine
