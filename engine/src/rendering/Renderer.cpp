#include "Renderer.hpp"

#include <raylib.h>

namespace kine
{

Renderer::Renderer(ResourceManager* resourceManager, RenderList* renderList, RenderBatcher* batch)
    : resources(resourceManager), list(renderList), batcher(batch)
{
}

Renderer::~Renderer() { shutdown(); }

void Renderer::init(int width, int height, const char* title)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    SetTargetFPS(144);
    InitWindow(width, height, title);
}

void Renderer::beginFrame()
{
    // For future use
}

void Renderer::endFrame() { list->clear(); }

void Renderer::shutdown()
{
    if (virtualEnabled)
    {
        UnloadRenderTexture(virtualTarget);
        virtualEnabled = false;
    }

    CloseWindow();
}

void Renderer::setVirtualResolution(int width, int height)
{
    if (virtualEnabled) UnloadRenderTexture(virtualTarget);

    virtualTarget = LoadRenderTexture(width, height);
    virtualWidth = width;
    virtualHeight = height;
    virtualEnabled = true;
}

void Renderer::disableVirtualResolution()
{
    if (virtualEnabled)
    {
        UnloadRenderTexture(virtualTarget);
        virtualEnabled = false;
    }
}

void Renderer::computeVirtualScaling(int windowW, int windowH)
{
    const float targetAspect = float(virtualWidth) / float(virtualHeight);
    const float windowAspect = float(windowW) / float(windowH);

    switch (scalingMode)
    {
    case ScalingMode::PixelPerfectInteger:
    {
        int scale = std::min(windowW / virtualWidth, windowH / virtualHeight);
        if (scale < 1) scale = 1;

        finalScaleX = finalScaleY = float(scale);
        int scaledW = virtualWidth * scale;
        int scaledH = virtualHeight * scale;

        finalOffsetX = (windowW - scaledW) / 2;
        finalOffsetY = (windowH - scaledH) / 2;
    }
    break;

    case ScalingMode::FreeScale:
    {
        finalScaleX = float(windowW) / float(virtualWidth);
        finalScaleY = float(windowH) / float(virtualHeight);
        finalOffsetX = 0;
        finalOffsetY = 0;
    }
    break;

    case ScalingMode::LetterboxedAuto:
    {
        if (windowAspect > targetAspect)
        {
            finalScaleY = float(windowH) / float(virtualHeight);
            finalScaleX = finalScaleY;
        }
        else
        {
            finalScaleX = float(windowW) / float(virtualWidth);
            finalScaleY = finalScaleX;
        }

        int scaledW = int(finalScaleX * virtualWidth);
        int scaledH = int(finalScaleY * virtualHeight);

        finalOffsetX = (windowW - scaledW) / 2;
        finalOffsetY = (windowH - scaledH) / 2;
    }
    break;
    }
}

void Renderer::render()
{
    batcher->buildBatches(list->get());

    // if (virtualEnabled)
    //     drawBatchesVirtual();
    // else
    drawBatchesDirect();
};

void Renderer::drawBatches()
{
    const auto& batches = batcher->getBatches();
    for (const RenderBatch& batch : batches)
    {
        for (const RenderCommand* cmd : batch.commands)
        {
            switch (cmd->type)
            {
            case RenderType::Sprite:
            {
                const Texture2D* tex = static_cast<Texture2D*>(batch.texturePtr);
                drawSprite(cmd, tex);
                break;
            }
            case RenderType::Rect:
                drawRect(cmd);
                break;
            case RenderType::Circle:
                drawCircle(cmd);
                break;
            case RenderType::Line:
                drawLine(cmd);
                break;
            }
        }
    }
}

void Renderer::drawBatchesDirect()
{
    BeginDrawing();
    ClearBackground(Color{10, 10, 15, 255});

    drawBatches();

    EndDrawing();
}

void Renderer::drawBatchesVirtual()
{
    BeginTextureMode(virtualTarget);
    ClearBackground(Color{10, 10, 15, 255});

    drawBatches();

    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);

    int W = GetScreenWidth();
    int H = GetScreenHeight();
    computeVirtualScaling(W, H);

    Rectangle src{0, 0, float(virtualWidth), -float(virtualHeight)};
    Rectangle dst{float(finalOffsetX), float(finalOffsetY), float(virtualWidth) * finalScaleX,
                  float(virtualHeight) * finalScaleY};

    DrawTexturePro(virtualTarget.texture, src, dst, {0, 0}, 0.0f, WHITE);

    EndDrawing();
}

inline static Color toRayColor(const std::array<float, 4>& c)
{
    return Color{static_cast<unsigned char>((c[0] * 255)), static_cast<unsigned char>((c[1] * 255)),
                 static_cast<unsigned char>((c[2] * 255)), static_cast<unsigned char>((c[3] * 255))};
}

void Renderer::drawSprite(const RenderCommand* cmd, const Texture2D* tex)
{
    Rectangle src{0, 0, float(tex->width), float(tex->height)};
    Rectangle dst{cmd->x, cmd->y, tex->width * cmd->scale, tex->width * cmd->scale};
    Vector2 pivot{cmd->pivotX, cmd->pivotY};

    DrawTexturePro(*tex, src, dst, pivot, cmd->rotation, toRayColor(cmd->color));
}

void Renderer::drawRect(const RenderCommand* cmd)
{
    DrawRectangleV({cmd->x, cmd->y}, {cmd->width * cmd->scale, cmd->height * cmd->scale}, toRayColor(cmd->color));
}

void Renderer::drawCircle(const RenderCommand* cmd)
{
    DrawCircleV({cmd->x, cmd->y}, cmd->radius, toRayColor(cmd->color));
}

void Renderer::drawLine(const RenderCommand* cmd)
{
    DrawLineEx({cmd->x, cmd->y}, {cmd->x2, cmd->y2}, cmd->radius * cmd->scale, toRayColor(cmd->color));
}

void Renderer::drawDebugOverlay()
{
    // TODO: maybe a debug?
}

}  // namespace kine
