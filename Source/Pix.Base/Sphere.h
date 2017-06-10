#pragma once

#include <math.h>

#include "General.h"
#include "Vector3.h"
#include "IntersectionData.h"
#include "Ray.h"
#include "Geometry.h"

namespace Pix::Base::Geometries
{
    class __declspec(align(16)) Sphere : public Geometry
    {
    public:
        Vector3 Position;
        float Radius;

        Sphere() = default;
        Sphere(Vector3 position, float radius);

        virtual float IntersectRay(const Ray& ray, const Geometry** hitGeometry) const override;
        virtual void GetIntersectionData(const Ray& ray, float distance, IntersectionData* intersectionData) const override;
    };
}