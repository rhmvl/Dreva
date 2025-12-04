#pragma once

namespace dreva::engine
{
class Time
{
   public:
    float dt = 0.0f;
    float accumulator = 0.0f;
    float fixedDt = 1.0f / 60.0f; // 60Hz fixed systems

    void beginFrame();
};
}  // namespace dreva::engine
