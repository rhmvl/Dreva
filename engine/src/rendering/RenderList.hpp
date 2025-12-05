#pragma once
#include <vector>
#include "RenderCommand.hpp"

namespace dreva::engine
{
class RenderList
{
   public:
    void submit(const RenderCommand& cmd) { commands.push_back(cmd); }

    const std::vector<RenderCommand>& get() const { return commands; }
    void clear() { commands.clear(); }

   private:
    std::vector<RenderCommand> commands;
};
}  // namespace dreva::engine
