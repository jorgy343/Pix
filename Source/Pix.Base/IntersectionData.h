#pragma once

#include "Vector3.h"
#include "Geometry.h"

using namespace Pix::Base::Geometries;

namespace Pix::Base
{
    class IntersectionData
    {
    public:
        const Geometry* IntersectedGeometry;
        float Distance;
        Vector3 Point;
        Vector3 Normal;

        IntersectionData() = default;
        IntersectionData(const Geometry* intersectedGeometry, float distance, const Vector3& point, const Vector3& normal);
    };
}