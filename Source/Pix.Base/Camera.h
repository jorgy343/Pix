#pragma once

#include "Vector3.h"
#include "IntVector2.h"
#include "Ray.h"

using namespace Pix::Base;

namespace Pix::Base::Cameras
{
    class Camera
    {
    private:
        Vector3 _position;
        Vector3 _lookAt;
        Vector3 _up;

        int _screenWidth;
        int _screenHeight;

    protected:
        Camera(const Vector3& position, const Vector3& lookAt, const Vector3& up, int screenWidth, int screenHeight);

    public:
        virtual void CalculateRays(IntVector2 pixel, IntVector2 subPixelMax, IntVector2 subPixelStart, IntVector2 subPixelEnd, Ray* rays) const = 0;

        Vector3 GetPosition() const;
        void SetPosition(const Vector3& position);

        Vector3 GetLookAt() const;
        void SetLookAt(const Vector3& lookAt);

        Vector3 GetUp() const;
        void SetUp(const Vector3& up);

        int GetScreenWidth() const;
        void SetScreenWidth(int screenWidth);

        int GetScreenHeight() const;
        void SetScreenHeight(int screenHeight);
    };
}