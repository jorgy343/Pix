#pragma once

#include "Color3.h"
#include "Geometry.h"
#include "Camera.h"
#include "SceneOptions.h"

using namespace Pix::Base;
using namespace Pix::Base::Geometries;
using namespace Pix::Base::Cameras;

namespace Pix::Engine
{
    class Scene
    {
    private:
        const SceneOptions* _options;
        const Camera* _camera;
        const Geometry* _rootGeometry;

        Color3 CastRay(const Ray& ray, int depth) const;

    public:
        Scene(const SceneOptions* options, const Camera* camera, const Geometry* rootGeometry);

        Color3 CastRay(const Ray& ray) const;
    };
}