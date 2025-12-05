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
     * @brief Adds a render command to the list.
     */
    void submit(const RenderCommand& cmd) { commands.push_back(cmd); }

    /**
     * @brief Returns all stored commands.
     */
    const std::vector<RenderCommand>& get() const { return commands; }

    /**
     * @brief Removes all commands after rendering.
     */
    void clear() { commands.clear(); }

   private:
    std::vector<RenderCommand> commands;  ///< All draw commands for current frame
};

}  // namespace kine
