#pragma once

#include "Vector3.h"

namespace Pix::Base
{
    class __declspec(align(16)) Ray
    {
    public:
        Vector3 Position;
        Vector3 Direction;

        Ray() = default;
        Ray(const Vector3& position, const Vector3& direction);
    };
}