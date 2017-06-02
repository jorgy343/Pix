#pragma once

#include <vector>
#include <random>

#include "General.h"
#include "Color3.h"
#include "Matrix33.h"
#include "MonteCarlo.h"
#include "Geometry.h"
#include "Camera.h"
#include "SceneOptions.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "IntersectionData.h"
#include "Material.h"
#include "DiffuseMaterial.h"
#include "MaterialManager.h"

using namespace Pix::Base;
using namespace Pix::Base::Geometries;
using namespace Pix::Base::Cameras;
using namespace Pix::Engine::Lights;
using namespace Pix::Engine::Materials;

namespace Pix::Engine
{
    class Scene
    {
    private:
        mutable std::mt19937 _generator;
        mutable std::uniform_real_distribution<float> _distribution;

        const SceneOptions* _options;
        const Camera* _camera;
        const std::vector<const Light*>* _lights;
        const Geometry* _rootGeometry;
        const MaterialManager* _materialManager;

        Color3 CastRay(const Ray& ray, int depth) const;

        Color3 CalculateLightPower(const IntersectionData* intersectionData) const;

    public:
        Scene(const SceneOptions* options, const Camera* camera, const std::vector<const Light*>* lights, const Geometry* rootGeometry, const MaterialManager* materialManager);

        Color3 CastRay(const Ray& ray) const;

        const SceneOptions* GetOptions() const;
        const Camera* GetCamera() const;
    };
}