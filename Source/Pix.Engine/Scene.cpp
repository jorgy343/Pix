#include "Scene.h"

using namespace Pix::Engine;

Scene::Scene(const SceneOptions* options, const Camera* camera, const std::vector<const Light*>* lights, const Geometry* rootGeometry)
    : _options(options), _camera(camera), _lights(lights), _rootGeometry(rootGeometry)
{

}

Color3 Scene::CastRay(const Ray& ray, IntersectionCallback intersectionCallback) const
{
    return CastRay(ray, intersectionCallback, 1);
}

Color3 Scene::CalculateLightPower(const IntersectionData* intersectionData) const
{
    IntersectionData dummyIntersectionData;
    Color3 lightPower(0.0f);

    for (const auto& light : *_lights)
    {
        bool inShadow = false;
        LightType lightType = light->GetType();

        if (lightType == LightType::Directional)
        {
            Ray shadowRay(intersectionData->GetPoint() + intersectionData->GetNormal() * Epsilon, ((DirectionalLight*)light)->GetReversedDirection());
            float shadowDistance = _rootGeometry->IntersectRay(shadowRay, &dummyIntersectionData);

            if (shadowDistance != INFINITY)
                inShadow = true;
        }
        else if (lightType == LightType::Point)
        {
            auto pointLight = (PointLight*)light;
            auto a = pointLight->GetPosition() - intersectionData->GetPoint();

            auto directionToLight = a.Normalize();
            auto distanceToLight = a.GetLength();

            Ray shadowRay(intersectionData->GetPoint() + directionToLight * Epsilon, directionToLight);
            float shadowDistance = _rootGeometry->IntersectRay(shadowRay, &dummyIntersectionData);

            if (shadowDistance != INFINITY)
                inShadow = true;
        }

        if (!inShadow)
            lightPower += light->CalculateIntensity(intersectionData->GetPoint(), intersectionData->GetNormal());
    }

    return lightPower;
}

Color3 Scene::CastRay(const Ray& ray, IntersectionCallback intersectionCallback, int depth) const
{
    IntersectionData intersectionData;
    float distance = _rootGeometry->IntersectRay(ray, &intersectionData);

    if (distance == INFINITY)
        return _options->GetDefaultColor();

    return CalculateLightPower(&intersectionData) * intersectionCallback(&intersectionData);
}

const SceneOptions* Scene::GetOptions() const
{
    return _options;
}

const Camera* Scene::GetCamera() const
{
    return _camera;
}