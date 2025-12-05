#include "Time.hpp"

#include <raylib.h>

namespace kine
{

void Time::beginFrame()
{
    dt = GetFrameTime();
    accumulator += dt;
}

}  // namespace kine
