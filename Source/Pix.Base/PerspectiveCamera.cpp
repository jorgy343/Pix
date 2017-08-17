#include "PerspectiveCamera.h"

using namespace Pix::Base::Cameras;

PerspectiveCamera::PerspectiveCamera(const Vector3& position, const Vector3& lookAt, const Vector3& up, int screenWidth, int screenHeight, float fieldOfView)
    : Camera(position, lookAt, up, screenWidth, screenHeight), _fieldOfView(fieldOfView), _random(RandomSse())
{

}

void PerspectiveCamera::CalculateRays(IntVector2 pixel, IntVector2 subPixelMax, IntVector2 subPixelStart, IntVector2 subPixelEnd, Ray* rays) const
{
    Vector3 direction = (GetLookAt() - GetPosition()).Normalize();

    Vector3 du = -Vector3::CrossProduct(GetUp(), direction).Normalize();
    Vector3 dv = -Vector3::CrossProduct(du, direction).Normalize();

    float halfWidth = tan(_fieldOfView / 2.0f);
    float halfHeight = GetScreenHeight() / GetScreenWidth() * halfWidth;

    du *= 2.0f * halfWidth / GetScreenWidth();
    dv *= 2.0f * halfWidth / GetScreenWidth();

    int index = 0;
    for (int subPixelY = subPixelStart.Y; subPixelY <= subPixelEnd.Y; ++subPixelY)
    {
        for (int subPixelX = subPixelStart.X; subPixelX <= subPixelEnd.X; ++subPixelX)
        {
            // Gives us the upper left coordinates of the pixel.
            float pixelIndexX = pixel.X - 0.5f * GetScreenWidth();
            float pixelIndexY = pixel.Y - 0.5f * GetScreenHeight();

            float random[4];
            _random.GetNextFloat(random);

            // Takes the upper left coordinates of the pixel and add an offset which will give us the coordinates somewhere inside
            // of the pixel. Multiply that by the delta direction to get the actual direction for the pixel.
            Vector3 u = (pixelIndexX + ((float)subPixelX + random[0]) / (float)subPixelMax.X) * du;
            Vector3 v = (pixelIndexY + ((float)subPixelY + random[1]) / (float)subPixelMax.Y) * dv;

            rays[index].Position = GetPosition();
            rays[index].Direction = (direction + u + v).Normalize();

            ++index;
        }
    }
}

float PerspectiveCamera::GetFieldOfView() const
{
    return _fieldOfView;
}

void PerspectiveCamera::SetFieldOfView(float fieldOfView)
{
    _fieldOfView = fieldOfView;
}