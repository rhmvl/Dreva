#include "Renderer.hpp"

#include <raylib.h>

namespace kine
{

Renderer::Renderer(ResourceManager* resourceManager, RenderList* renderList)
    : resources(resourceManager), list(renderList)
{
}

void Renderer::init(int width, int height, const char* title)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    SetTargetFPS(144);
    InitWindow(width, height, title);
}

void Renderer::render()
{
    BeginDrawing();
    ClearBackground(Color{10, 10, 15, 255});

    for (const auto& cmd : list->get())
    {
        if (!cmd.texture || cmd.texture->id == 0) continue;

        DrawTexturePro(
            *cmd.texture, {0, 0, static_cast<float>(cmd.texture->width), static_cast<float>(cmd.texture->height)},
            {cmd.position.x, cmd.position.y, cmd.texture->width * cmd.scale, cmd.texture->height * cmd.scale},
            {cmd.pivot.x, cmd.pivot.y}, cmd.rotation, cmd.tint);
    }

    EndDrawing();
};

}  // namespace kine
