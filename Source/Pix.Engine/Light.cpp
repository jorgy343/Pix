#include "Light.h"

using namespace Pix::Engine::Lights;

Light::Light(LightType type, const Color3& color)
    : _type(type), _color(color)
{

}

LightType Light::GetType() const
{
    return _type;
}

Color3 Light::GetColor() const
{
    return _color;
}