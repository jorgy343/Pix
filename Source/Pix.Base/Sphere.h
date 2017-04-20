#pragma once

#include "Constants.h"
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

        virtual const Geometry* IntersectRay(const Ray& ray, IntersectionData* intersectionData) const override;
    };
}