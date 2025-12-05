#pragma once

namespace kine
{

/**
 * @class Time
 * @brief Tracks per-frame delta time and fixed update timing.
 *
 * The Time system stores variable `dt` (delta time), accumulates time for
 * fixed-rate updates, and exposes a fixed timestep (default 60Hz).
 */
class Time
{
   public:
    float dt = 0.0f;               ///< Variable delta time between frames
    float accumulator = 0.0f;      ///< Accumulated time for fixed updates
    float fixedDt = 1.0f / 60.0f;  ///< Fixed update step duration

    /**
     * @brief Called at the start of each frame to update delta time.
     */
    void beginFrame();
};

}  // namespace kine
