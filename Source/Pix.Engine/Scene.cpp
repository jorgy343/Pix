#include "Scene.h"

using namespace Pix::Engine;

Scene::Scene(const SceneOptions* options, const Camera* camera, const std::vector<const Light*>* lights, const Geometry* rootGeometry)
    : _options(options), _camera(camera), _lights(lights), _rootGeometry(rootGeometry)
{

}

Color3 Scene::CastRay(const Ray& ray, int depth) const
{
    IntersectionData intersectionData;
    float distance = _rootGeometry->IntersectRay(ray, &intersectionData);

    if (distance == INFINITY)
        return _options->GetDefaultColor();

    Color3 lightPower(0.0f);
    for (const auto& light : *_lights)
    {
        lightPower += light->CalculateIntensity(intersectionData.GetPoint(), intersectionData.GetNormal());
    }

    return lightPower;
}

Color3 Scene::CastRay(const Ray& ray) const
{
    return CastRay(ray, 1);
}

const SceneOptions* Scene::GetOptions() const
{
    return _options;
}

const Camera* Scene::GetCamera() const
{
    return _camera;
}