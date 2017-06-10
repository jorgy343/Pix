#pragma once

#include <math.h>

#include "Vector3.h"
#include "IntersectionData.h"
#include "Ray.h"
#include "Geometry.h"

namespace Pix::Base::Geometries
{
    class __declspec(align(16)) Plane : public Geometry
    {
    public:
        Vector3 Normal;
        float D;

        Plane() = default;
        Plane(Vector3 normal, float d);
        Plane(Vector3 normal, Vector3 point);

        virtual float IntersectRay(const Ray& ray, const Geometry** hitGeometry) const override;
        virtual void GetIntersectionData(const Ray& ray, float distance, IntersectionData* intersectionData) const override;
    };
}