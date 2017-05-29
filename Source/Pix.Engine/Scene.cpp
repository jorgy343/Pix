#include "Scene.h"

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

std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(0, 1);

Color3 Scene::CastRay(const Ray& ray, int depth) const
{
    if (depth > 4)
        return Color3(0);

    IntersectionData intersectionData;
    float distance = _rootGeometry->IntersectRay(ray, &intersectionData);

    if (distance == INFINITY)
        return _options->GetDefaultColor();

    const Material* material = _materialManager->GetMaterialForGeometry(intersectionData.GetIntersectedGeometry());
    if (material->Type == MaterialType::Diffuse)
    {
        const DiffuseMaterial* diffuseMaterial = (const DiffuseMaterial*)material;

        Vector3 tangent;
        Vector3 bitangent;

        MonteCarlo::CreateTangentCoordinateSystem(intersectionData.GetNormal(), &tangent, &bitangent);
        Color3 indirectDiffuse(0);
        Matrix33 tangentSpaceToWorldSpaceTransform(tangent, intersectionData.GetNormal(), bitangent);

        const int sampleCount = 256;
        for (int i = 0; i < sampleCount; ++i)
        {
            float random1 = distribution(generator);
            float random2 = distribution(generator);

            Vector3 tangentSpaceSample = MonteCarlo::CosineWeightedSampleHemisphere(random1, random2);
            Vector3 worldSpaceSample = tangentSpaceSample * tangentSpaceToWorldSpaceTransform;

            auto castColor = CastRay(Ray(intersectionData.GetPoint() + intersectionData.GetNormal() * Epsilon, worldSpaceSample), depth + 1);
            indirectDiffuse += castColor;
        }

        indirectDiffuse /= (float)sampleCount;
        return (CalculateLightPower(&intersectionData) / Pi<float> + indirectDiffuse) * diffuseMaterial->Color;
    }

    return _options->GetDefaultColor();
}

const SceneOptions* Scene::GetOptions() const
{
    return _options;
}

const Camera* Scene::GetCamera() const
{
    return _camera;
}