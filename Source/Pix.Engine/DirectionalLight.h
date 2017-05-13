#pragma once

#include "Vector3.h"
#include "Light.h"

using namespace Pix::Base;

namespace Pix::Engine::Lights
{
    class DirectionalLight : public Light
    {
    private:
        Vector3 _direction;
        Vector3 _reversedDirection;

    public:
        DirectionalLight(const Color3& color, const Vector3& direction);

        Color3 CalculateIntensity(const Vector3& point, const Vector3& normal) const override;

        Vector3 GetDirection() const;
        Vector3 GetReversedDirection() const;
    };
}