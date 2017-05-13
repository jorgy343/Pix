#pragma once

#include "Vector3.h"
#include "Light.h"

using namespace Pix::Base;

namespace Pix::Engine::Lights
{
    class PointLight : public Light
    {
    private:
        Vector3 _position;

    public:
        PointLight(const Color3& color, const Vector3& position);

        Color3 CalculateIntensity(const Vector3& point, const Vector3& normal) const override;

        Vector3 GetPosition() const;
    };
}