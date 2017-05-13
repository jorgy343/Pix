#pragma once

#include "Color3.h"
#include "Vector3.h"
#include "LightType.h"

using namespace Pix::Base;

namespace Pix::Engine::Lights
{
    class Light
    {
    protected:
        LightType _type;
        Color3 _color;

    public:
        Light(LightType type, const Color3& color);

        virtual Color3 CalculateIntensity(const Vector3& point, const Vector3& normal) const = 0;

        LightType GetType() const;
        Color3 GetColor() const;
    };
}