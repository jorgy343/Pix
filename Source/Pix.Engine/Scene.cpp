#include "Scene.h"

using namespace Pix::Engine;

Scene::Scene(const SceneOptions* options, const Camera* camera, const std::vector<const Light*>* lights, const Geometry* rootGeometry, const MaterialManager* materialManager)
    : _generator{std::random_device{ }()}, _options(options), _camera(camera), _lights(lights), _rootGeometry(rootGeometry), _materialManager(materialManager),
    _rng(
        std::random_device{ }(),
        std::random_device{ }(),
        std::random_device{ }(),
        std::random_device{ }(),
        std::random_device{ }(),
        std::random_device{ }(),
        std::random_device{ }(),
        std::random_device{ }())
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
            Ray shadowRay(intersectionData->Point + intersectionData->Normal * Epsilon, ((DirectionalLight*)light)->GetReversedDirection());
            float shadowDistance = _rootGeometry->IntersectRay(shadowRay, &dummyIntersectionData);

            if (shadowDistance != INFINITY)
                inShadow = true;
        }
        else if (lightType == LightType::Point)
        {
            auto pointLight = (PointLight*)light;
            auto directionToLight = (pointLight->GetPosition() - intersectionData->Point).Normalize();

            Ray shadowRay(intersectionData->Point + directionToLight * Epsilon, directionToLight);
            float shadowDistance = _rootGeometry->IntersectRay(shadowRay, &dummyIntersectionData);

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
        return Color3(0);

    IntersectionData intersectionData;
    float distance = _rootGeometry->IntersectRay(ray, &intersectionData);

    if (distance == INFINITY) // Ray missed all geometry.
        return _options->GetDefaultColor();

    const Material* material = _materialManager->GetMaterialForGeometry(intersectionData.IntersectedGeometry);
    if (material->Type == MaterialType::MonteCarloDiffuse)
    {
        const MonteCarloDiffuseMaterial* monteCarloDiffuseMaterial = (const MonteCarloDiffuseMaterial*)material;

        Vector3 tangent;
        Vector3 bitangent;

        MonteCarlo::CreateTangentCoordinateSystem(intersectionData.Normal, &tangent, &bitangent);
        Matrix33 tangentSpaceToWorldSpaceTransform(tangent, intersectionData.Normal, bitangent);

        Color3 indirectLight(0);
        const int sampleCount = (_options->GetMaxDepth() - depth + 1) * 2;
        //const int sampleCount = 1;

        for (int i = 0; i < sampleCount; ++i)
        {
            float random1[4];
            float random2[4];

            _rng.GetNextFloat(random1);
            _rng.GetNextFloat(random2);

            Vector3 samples[4];
            MonteCarlo::CosineWeightedSampleHemisphere4(samples, random1, random2);

            for (int i = 0; i < 4; ++i)
            {
                Vector3 sample = samples[i] * tangentSpaceToWorldSpaceTransform;

                Ray ray(intersectionData.Point + intersectionData.Normal * Epsilon, samples[i]);
                indirectLight += CastRay(ray, depth + 1);
            }


            //float random1 = (float)_generator() / 4294967295.0f;
            //float random2 = (float)_generator() / 4294967295.0f;

            //Vector3 tangentSpaceSample = MonteCarlo::CosineWeightedSampleHemisphere(random1, random2);
            //Vector3 worldSpaceSample = tangentSpaceSample * tangentSpaceToWorldSpaceTransform;

            //Ray ray(intersectionData.Point + intersectionData.Normal * Epsilon, worldSpaceSample);
            //indirectLight += CastRay(ray, depth + 1);


            //Ray ray = MonteCarlo::WeirdThingThatMightWork(intersectionData.GetPoint(), intersectionData.GetNormal(), random1, random2);
            //indirectLight += CastRay(ray, depth + 1);
        }

        indirectLight /= (float)sampleCount * 4.0f;
        return (CalculateLightPower(&intersectionData) * OneOverPi<float> + indirectLight) * monteCarloDiffuseMaterial->Color;
    }

    // Unknown material type.
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