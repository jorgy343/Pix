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
        virtual float IntersectRay(const Ray& ray, const Geometry** hitGeometry) const = 0;
        virtual void GetIntersectionData(const Ray& ray, float distance, IntersectionData* intersectionData) const = 0;
    };
}