#include "DirectionalLight.h"

using namespace Pix::Engine::Lights;

DirectionalLight::DirectionalLight(const Color3& color, const Vector3& direction)
    : Light(color), _direction(direction), _reversedDirection(Vector3::Negate(direction))
{

}

Color3 DirectionalLight::CalculateIntensity(const Vector3& point, const Vector3& normal) const
{
    return _color * std::max(0.0f, Vector3::Dot(normal, _reversedDirection));
}