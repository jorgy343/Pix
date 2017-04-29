#pragma once

#include "Color3.h"
#include "Geometry.h"

using namespace Pix::Base;
using namespace Pix::Base::Geometries;

namespace Pix::Engine
{
    class Scene
    {
    private:
        Color3 _backgroundColor;
        const Geometry* _rootGeometry;

        Color3 CastRay(const Ray& ray, int depth) const;

    public:
        Scene(const Color3& backgroundColor, const Geometry* rootGeometry);

        Color3 CastRay(const Ray& ray);
    };
}