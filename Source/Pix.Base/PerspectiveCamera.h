#pragma once

#include "RandomSse.h"
#include "Camera.h"
#include "Vector3.h"
#include "Ray.h"

namespace Pix::Base::Cameras
{
    class PerspectiveCamera : public Camera
    {
    private:
        float _fieldOfView;

    protected:
        mutable RandomSse _random;

    public:
        PerspectiveCamera(const Vector3& position, const Vector3& lookAt, const Vector3& up, int screenWidth, int screenHeight, float fieldOfView);

        virtual void CalculateRays(int x, int y, int level, Ray* rays) const override;

        float GetFieldOfView() const;
        void SetFieldOfView(float fieldOfView);
    };
}