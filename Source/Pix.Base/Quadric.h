#pragma once

#include "Vector4.h"
#include "Matrix.h"
#include "IntersectionData.h"
#include "Geometry.h"

namespace Pix::Base::Geometries
{
    class __declspec(align(16)) Quadric : public Geometry
    {
    public:
        float A, B, C, D, E, F, G, H, I, J;

        Quadric() = default;
        Quadric(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j);

        virtual float IntersectRay(const Ray& ray, IntersectionData* intersectionData) const override;
    };
}