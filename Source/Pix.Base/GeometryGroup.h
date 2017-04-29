#pragma once

#include <vector>
#include <float.h>

#include "Geometry.h"
#include "IntersectionData.h"

namespace Pix::Base::Geometries
{
    class GeometryGroup : public Geometry
    {
    private:
        const std::vector<const Geometry*>* _geometries;

    public:
        GeometryGroup(const std::vector<const Geometry*>* geometries);

        virtual float IntersectRay(const Ray& ray, IntersectionData* intersectionData) const override;
    };
}