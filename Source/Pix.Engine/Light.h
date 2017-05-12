#pragma once

#include "Color3.h"
#include "Vector3.h"

using namespace Pix::Base;

namespace Pix::Engine::Lights
{
    class Light
    {
    protected:
        Color3 _color;

    public:
        explicit Light(const Color3& color);

        virtual Color3 CalculateIntensity(const Vector3& point, const Vector3& normal) const = 0;
    };
}