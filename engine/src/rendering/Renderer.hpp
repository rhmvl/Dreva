#pragma once
#include "../resources/ResourceManager.hpp"

namespace dreva::engine
{

class Renderer
{
   public:
    explicit Renderer(ResourceManager* resourceManager);
    ~Renderer() = default;

    void init();
    void render();

   private:
    ResourceManager* resources;
};
}  // namespace dreva::engine
