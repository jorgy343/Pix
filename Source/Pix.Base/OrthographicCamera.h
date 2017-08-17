#pragma once

#include "Random.h"
#include "Camera.h"
#include "Vector3.h"
#include "IntVector2.h"
#include "Ray.h"

using namespace Pix::Base;

namespace Pix::Base::Cameras
{
    class OrthographicCamera : public Camera
    {
    private:
        float _orthoWidth;
        float _orthoHeight;

    protected:
        mutable Random _random;

    public:
        OrthographicCamera(const Vector3& position, const Vector3& lookAt, const Vector3& up, int screenWidth, int screenHeight, float orthoWidth, float orthoHeight);

        virtual void CalculateRays(IntVector2 pixel, IntVector2 subPixelMax, IntVector2 subPixelStart, IntVector2 subPixelEnd, Ray* rays) const override;

        float GetOrthoWidth() const;
        void SetOrthoWidth(float orthoWidth);

        float GetOrthoHeight() const;
        void SetOrthoHeight(float orthoHeight);
    };
}