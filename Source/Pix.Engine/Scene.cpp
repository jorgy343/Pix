#include "Scene.h"
#include "General.h"
#include "Matrix33.h"
#include "MonteCarlo.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Material.h"
#include "PhongDiffuseMaterial.h"
#include "MonteCarloDiffuseMaterial.h"

using namespace Pix::Engine;

Scene::Scene(const SceneOptions* options, const Camera* camera, const std::vector<const Light*>* lights, const Geometry* rootGeometry, const MaterialManager* materialManager)
    : _options(options), _camera(camera), _lights(lights), _rootGeometry(rootGeometry), _materialManager(materialManager)
{

}

Color3 Scene::CastRay(const Ray& ray) const
{
    return CastRay(ray, 1);
}

Color3 Scene::CalculateLightPower(const IntersectionData* intersectionData) const
{
    const Geometry* dummyHitGeometry;
    Color3 lightPower(0.0f);

    for (const auto& light : *_lights)
    {
        bool inShadow = false;
        LightType lightType = light->GetType();

        if (lightType == LightType::Directional)
        {
            Ray shadowRay(intersectionData->Point + intersectionData->Normal * Epsilon, ((DirectionalLight*)light)->GetReversedDirection());
            float shadowDistance = _rootGeometry->IntersectRay(shadowRay, &dummyHitGeometry);

            if (shadowDistance != INFINITY)
                inShadow = true;
        }
        else if (lightType == LightType::Point)
        {
            auto pointLight = (PointLight*)light;
            auto directionToLight = (pointLight->GetPosition() - intersectionData->Point).Normalize();

            Ray shadowRay(intersectionData->Point + directionToLight * Epsilon, directionToLight);
            float shadowDistance = _rootGeometry->IntersectRay(shadowRay, &dummyHitGeometry);

            if (shadowDistance < (pointLight->GetPosition() - intersectionData->Point).GetLength())
                inShadow = true;
        }

        if (!inShadow)
            lightPower += light->CalculateIntensity(intersectionData->Point, intersectionData->Normal);
    }

    return lightPower;
}

Color3 Scene::CastRay(const Ray& ray, int depth) const
{
    if (depth > _options->GetMaxDepth())
        return Color3(0.0f);

    IntersectionData intersectionData;
    const Geometry* hitGeometry;

    float distance = _rootGeometry->IntersectRay(ray, &hitGeometry);
    if (distance == INFINITY) // Ray missed all geometry.
        return _options->GetDefaultColor();

    hitGeometry->GetIntersectionData(ray, distance, &intersectionData);

    const Material* material = _materialManager->GetMaterialForGeometry(intersectionData.IntersectedGeometry);
    if (material->Type == MaterialType::PhongDiffuse)
    {
        const PhongDiffuseMaterial* monteCarloDiffuseMaterial = (const PhongDiffuseMaterial*)material;
        return CalculateLightPower(&intersectionData) * monteCarloDiffuseMaterial->DiffuseColor * monteCarloDiffuseMaterial->DiffuseCoefficient;
    }
    else if (material->Type == MaterialType::MonteCarloDiffuse)
    {
        const MonteCarloDiffuseMaterial* monteCarloDiffuseMaterial = (const MonteCarloDiffuseMaterial*)material;
        Color3 indirectLight(0.0f);

        float random[4];
        _rng.GetNextFloat(random);

        float russianRouletteFactor = 1.0f;
        if (depth >= _options->GetRussianRouletteDepthStart())
        {
            if (random[0] <= _options->GetRussianRouletteStopFactor())
                return Color3(0.0f);

            russianRouletteFactor = 1.0f / (1.0f - _options->GetRussianRouletteStopFactor());
        }

        if (depth < _options->GetMaxDepth()) // Don't even compute monte carlo rays if the call is simply going to return Color3(0).
        {
            Vector3 tangent;
            Vector3 bitangent;

            MonteCarlo::CreateTangentCoordinateSystem(intersectionData.Normal, &tangent, &bitangent);
            Matrix33 tangentSpaceToWorldSpaceTransform(tangent, intersectionData.Normal, bitangent);

            Vector3 tangentSpaceSample = MonteCarlo::CosineWeightedSampleHemisphere(random[1], random[2]);
            Vector3 worldSpaceSample = tangentSpaceSample * tangentSpaceToWorldSpaceTransform;

            Ray ray(intersectionData.Point + intersectionData.Normal * Epsilon, worldSpaceSample);
            indirectLight = CastRay(ray, depth + 1);
        }

        return monteCarloDiffuseMaterial->EmissiveColor * russianRouletteFactor + (CalculateLightPower(&intersectionData) * OneOverPi<float> + indirectLight) * monteCarloDiffuseMaterial->Color * russianRouletteFactor;
    }
    else if (material->Type == MaterialType::Specular)
    {
        Vector3 reflectionDirection = Vector3::Reflect(ray.Direction, intersectionData.Normal);
        Ray ray(intersectionData.Point + intersectionData.Normal * Epsilon, reflectionDirection);

        return CastRay(ray, depth + 1);
    }

    // Unknown material type.
    return Color3(0.0f);
}

const SceneOptions* Scene::GetOptions() const
{
    return _options;
}

const Camera* Scene::GetCamera() const
{
    return _camera;
}