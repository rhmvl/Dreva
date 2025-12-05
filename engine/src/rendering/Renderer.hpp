#pragma once
#include "../resources/ResourceManager.hpp"
#include "rendering/RenderList.hpp"

namespace dreva::engine
{

class Renderer
{
   public:
    explicit Renderer(ResourceManager* resourceManager, RenderList* list);
    ~Renderer() = default;

    void init(int width, int height, const char* title);
    void render();

   private:
    ResourceManager* resources;
    RenderList* list;
};
}  // namespace dreva::engine
