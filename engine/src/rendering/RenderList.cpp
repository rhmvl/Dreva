#include "RenderList.hpp"

namespace kine
{

RenderList::RenderList() { commands.reserve(1024); }

void RenderList::addSprite(const std::string& texture, float x, float y, float rotation, float pivotX, float pivotY,
                           float scale, int32_t layer)
{
    RenderCommand cmd{};
    cmd.type = RenderType::Sprite;
    cmd.textureName = texture;
    cmd.x = x;
    cmd.y = y;
    cmd.rotation = rotation;
    cmd.pivotX = pivotX;
    cmd.pivotY = pivotY;
    cmd.scale = scale;
    cmd.layer = layer;

    commands.push_back(cmd);
}

void RenderList::addRect(float x, float y, float w, float h, std::array<float, 4> color, float scale, int32_t layer)
{
    RenderCommand cmd{};
    cmd.type = RenderType::Rect;
    cmd.x = x;
    cmd.y = y;
    cmd.width = w;
    cmd.height = h;
    cmd.scale = scale;
    cmd.color = color;
    cmd.layer = layer;

    commands.push_back(cmd);
}

void RenderList::addCircle(float x, float y, float radius, std::array<float, 4> color, float scale, int32_t layer)
{
    RenderCommand cmd{};
    cmd.type = RenderType::Circle;
    cmd.x = x;
    cmd.y = y;
    cmd.radius = radius;
    cmd.scale = scale;
    cmd.color = color;
    cmd.layer = layer;

    commands.push_back(cmd);
}

void RenderList::addLine(float x1, float y1, float x2, float y2, float thickness, std::array<float, 4> color,
                         float scale, int32_t layer)
{
    RenderCommand cmd{};
    cmd.type = RenderType::Line;
    cmd.x = x1;
    cmd.y = y1;
    cmd.x2 = x2;
    cmd.y2 = y2;
    cmd.radius = thickness;
    cmd.scale = scale;
    cmd.color = color;
    cmd.layer = layer;

    commands.push_back(cmd);
}

}  // namespace kine
