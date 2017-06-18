#include "PerspectiveCamera.h"

using namespace Pix::Base::Cameras;

PerspectiveCamera::PerspectiveCamera(const Vector3& position, const Vector3& lookAt, const Vector3& up, int screenWidth, int screenHeight, float fieldOfView)
    : Camera(position, lookAt, up, screenWidth, screenHeight), _fieldOfView(fieldOfView), _random(RandomSse())
{

}

void PerspectiveCamera::CalculateRays(int x, int y, int level, Ray* rays) const
{
    Vector3 direction = (GetLookAt() - GetPosition()).Normalize();

    Vector3 du = Vector3::CrossProduct(GetUp(), direction).Normalize();
    Vector3 dv = Vector3::CrossProduct(du, direction).Normalize();

    float incrementBase = 2.0f * tan(_fieldOfView /  2.0f) / GetScreenWidth();

    du *= incrementBase;
    dv *= incrementBase;

    for (int i = 0; i < level; ++i)
    {
        for (int j = 0; j < level; ++j)
        {
            // Gives us the upper left coordinates of the pixel.
            float pixelIndexX = y - 0.5f * GetScreenHeight();
            float pixelIndexY = x - 0.5f * GetScreenWidth();

            int index = i * level + j;

            float random[4];
            _random.GetNextFloat(random);

            // Takes the upper left coordinates of the pixel and add an offset which will give us the coordinates somewhere inside
            // of the pixel. Multiply that by the delta direction to get the actual direction for the pixel.
            Vector3 u = (pixelIndexY + ((float)i + random[0]) / (float)level) * du;
            Vector3 v = (pixelIndexX + ((float)j + random[1]) / (float)level) * dv;

            rays[index].Position = GetPosition();
            rays[index].Direction = (direction + u + v).Normalize();
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