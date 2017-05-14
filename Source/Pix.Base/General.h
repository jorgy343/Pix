#pragma once

#include <functional>

#include "Color3.h"
#include "IntersectionData.h"

namespace Pix::Base
{
    const float Epsilon = 0.1f;

    using IntersectionCallback = std::function<Color3(const IntersectionData*)>;
}