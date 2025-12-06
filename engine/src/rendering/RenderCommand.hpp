#pragma once
#include <array>
#include <glm/vec2.hpp>
#include <string>

namespace kine
{

/**
 * @enum RenderType
 * @brief Identifies which primitive the renderer should draw.
 *
 * - Sprite DrawTexturePro
 * - Rect   DrawRectangleV
 * - Circle DrawCircleV
 * - Line   DrawLineEx
 */
enum class RenderType : uint8_t
{
    Sprite,
    Rect,
    Circle,
    Line
};

/**
 * @struct RenderCommand
 * @brief A fully resolved "draw call request" submitted each frame.
 */
struct RenderCommand
{
    RenderType type{RenderType::Sprite};  ///< Type of draw operation
    int32_t layer{0};                     ///< Draw order (lower = earlier, stable sorted)

    std::string textureName{};

    float x{0.0f};         ///< World-space X position
    float y{0.0f};         ///< World-space Y position
    float width{0.0f};     ///< Sprite or rect width
    float height{0.0f};    ///< Sprite or rect height
    float rotation{0.0f};  ///< Rotation in degrees
    float scale{0.0f};     ///< Scale

    float pivotX{0.0f};  ///< Pivot X offset for rotation
    float pivotY{0.0f};  ///< Pivot Y offset for rotation

    float radius{0.0f};  ///< Circle radius or line thickness
    float x2{0.0f};      ///< Line end x
    float y2{0.0f};      ///< Line end y

    /**
     * @brief RGBA color, float-based, deterministic.
     */
    std::array<float, 4> color{1.0f, 1.0f, 1.0f, 1.0f};
};

}  // namespace kine
