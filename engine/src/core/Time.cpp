#include "Time.hpp"

#include <raylib.h>

namespace dreva::engine
{

void Time::beginFrame()
{
    dt = GetFrameTime();
    accumulator += dt;
}

}  // namespace dreva::engine
