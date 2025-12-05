#pragma once
#include <raylib.h>
#include <glm/vec2.hpp>

namespace dreva::engine
{
struct RenderCommand
{
    Texture2D* texture = nullptr;
    glm::vec2 position{0, 0};
    glm::vec2 pivot{0, 0};
    float rotation = 0.0f;
    float scale = 1.0f;
    Color tint = WHITE;
};
}  // namespace dreva::engine
