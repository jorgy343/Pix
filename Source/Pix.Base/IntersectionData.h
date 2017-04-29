#pragma once

#include "Vector3.h"
#include "Geometry.h"

using namespace Pix::Base::Geometries;

namespace Pix::Base
{
    class IntersectionData
    {
    private:
        const Geometry* _intersectedGeometry;
        float _distance;
        Vector3 _point;
        Vector3 _normal;

    public:
        IntersectionData() = default;
        IntersectionData(const Geometry* intersectedGeometry, float distance, const Vector3& point, const Vector3& normal);

        float GetDistance() const;
        void SetDistance(float distance);

        Vector3 GetPoint() const;
        void SetPoint(const Vector3& point);

        Vector3 GetNormal() const;
        void SetNormal(const Vector3& normal);
    };
}