#include "OrthographicCamera.h"

using namespace Pix::Base::Cameras;

OrthographicCamera::OrthographicCamera(const Vector3& position, const Vector3& lookAt, const Vector3& up, int screenWidth, int screenHeight, float orthoWidth, float orthoHeight)
    : Camera(position, lookAt, up, screenWidth, screenHeight), _orthoWidth(orthoWidth), _orthoHeight(orthoHeight), _random(Random())
{

}

void OrthographicCamera::CalculateRays(int x, int y, int level, Ray* rays) const
{
    Vector3 direction = (GetPosition() - GetLookAt()).Normalize();

    Vector3 u = Vector3::CrossProduct(GetUp(), direction).Normalize() * _orthoWidth;
    Vector3 v = Vector3::CrossProduct(u, direction).Normalize() * _orthoHeight;

    float deltaX = (float)x / (float)GetScreenWidth();
    float deltaY = (float)y / (float)GetScreenHeight();

    float subDeltaX = 1.0f / (float)GetScreenWidth() / (float)level;
    float subDeltaY = 1.0f / (float)GetScreenHeight() / (float)level;

    Vector3 corner = GetPosition() - u / 2.0f - v / 2.0f;
    for (int i = 0; i < level; ++i)
    {
        for (int j = 0; j < level; ++j)
        {
            int index = i * level + j;

            rays[index].Position = corner + (deltaX + subDeltaX * j + subDeltaX * _random.GetNormalizedFloat()) * u + (deltaY + subDeltaY * i + subDeltaY * _random.GetNormalizedFloat()) * v;
            rays[index].Direction = direction;
        }
    }
}

float OrthographicCamera::GetOrthoWidth() const
{
    return _orthoWidth;
}

void OrthographicCamera::SetOrthoWidth(float orthoWidth)
{
    _orthoWidth = orthoWidth;
}

float OrthographicCamera::GetOrthoHeight() const
{
    return _orthoHeight;
}

void OrthographicCamera::SetOrthoHeight(float orthoHeight)
{
    _orthoHeight = orthoHeight;
}