#include "Scene.h"

using namespace Pix::Engine;

Scene::Scene(const SceneOptions* options, const Camera* camera, const std::vector<const Light*>* lights, const Geometry* rootGeometry)
    : _options(options), _camera(camera), _lights(lights), _rootGeometry(rootGeometry)
{

}

Color3 Scene::CastRay(const Ray& ray, int depth) const
{
    return _options->GetDefaultColor();
}

Color3 Scene::CastRay(const Ray& ray) const
{
    return CastRay(ray, 1);
}