#pragma once
#include <raylib.h>
#include <glm/vec2.hpp>

namespace kine
{

/**
 * @struct RenderCommand
 * @brief Represents a single drawable sprite command submitted each frame.
 *
 * The Renderer receives these commands from the RenderList and draws them at
 * render time.
 */
struct RenderCommand
{
    Texture2D* texture = nullptr;  ///< Texture to draw
    glm::vec2 position{0, 0};      ///< World/screen position
    glm::vec2 pivot{0, 0};         ///< Pivot for rotation/scaling
    float rotation = 0.0f;         ///< Rotation in degrees
    float scale = 1.0f;            ///< Uniform scale factor
    Color tint = WHITE;            ///< Color tint applied to the texture
};

}  // namespace kine
