#pragma once

#include "Ray.h"

namespace Pix::Base
{
    class IntersectionData;
}

namespace Pix::Base::Geometries
{
    class Geometry
    {
    public:
        virtual float IntersectRay(const Ray& ray, IntersectionData* intersectionData) const = 0;
    };
}