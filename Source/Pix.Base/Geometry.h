#pragma once

#include "Ray.h"
#include "IntersectionData.h"

namespace Pix::Base::Geometries
{
    class Geometry
    {
    public:
        virtual const Geometry* IntersectRay(const Ray& ray, IntersectionData* intersectionData) const = 0;
    };
}