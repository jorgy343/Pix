#include "Camera.h"

using namespace Pix::Base::Cameras;

Camera::Camera(const Vector3& position, const Vector3& lookAt, const Vector3& up, int screenWidth, int screenHeight)
    : _position(position), _lookAt(lookAt), _up(up),
    _screenWidth(screenWidth), _screenHeight(screenHeight),
    _random(Random())
{

}

Vector3 Camera::GetPosition() const
{
    return _position;
}

void Camera::SetPosition(const Vector3& position)
{
    _position = position;
}

Vector3 Camera::GetLookAt() const
{
    return _lookAt;
}

void Camera::SetLookAt(const Vector3& direction)
{
    _lookAt = direction;
}

Vector3 Camera::GetUp() const
{
    return _up;
}

void Camera::SetUp(const Vector3& up)
{
    _up = up;
}

int Camera::GetScreenWidth() const
{
    return _screenWidth;
}

void Camera::SetScreenWidth(int screenWidth)
{
    _screenWidth = screenWidth;
}

int Camera::GetScreenHeight() const
{
    return _screenHeight;
}

void Camera::SetScreenHeight(int screenHeight)
{
    _screenHeight = screenHeight;
}