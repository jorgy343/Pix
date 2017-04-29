#include "Scene.h"

using namespace Pix::Engine;

Scene::Scene(const Color3& backgroundColor, const Geometry* rootGeometry)
    : _backgroundColor(backgroundColor), _rootGeometry(rootGeometry)
{

}

Color3 Scene::CastRay(const Ray& ray, int depth) const
{
    return _backgroundColor;
}

Color3 Scene::CastRay(const Ray& ray)
{
    return CastRay(ray, 1);
}