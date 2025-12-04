#include "Renderer.hpp"

#include <raylib.h>

namespace dreva::engine
{

Renderer::Renderer(ResourceManager* resourceManager) : resources(resourceManager) {}

void Renderer::init()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    SetTargetFPS(144);
    InitWindow(1280, 720, "Dreva");
}

void Renderer::render()
{
    BeginDrawing();
    ClearBackground(Color{10, 10, 15, 255});

    Texture2D& tex = resources->getTexture("error");
    DrawTextureEx(tex, {200, 300}, 0.0f, 1, WHITE);

    EndDrawing();
};

}  // namespace dreva::engine
