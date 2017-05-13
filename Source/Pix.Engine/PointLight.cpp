#include "PointLight.h"

using namespace Pix::Engine::Lights;

PointLight::PointLight(const Color3& color, const Vector3& position)
    : Light(LightType::Point, color), _position(position)
{

}

Color3 PointLight::CalculateIntensity(const Vector3& point, const Vector3& normal) const
{
    auto directionToLight = (_position - point).Normalize();
    return _color * std::max(0.0f, Vector3::Dot(normal, directionToLight));
}

Vector3 PointLight::GetPosition() const
{
    return _position;
}