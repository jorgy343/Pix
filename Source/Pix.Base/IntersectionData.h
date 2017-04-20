#pragma once

#include "Vector3.h"

namespace Pix::Base
{
    class IntersectionData
    {
    private:
        float _distance;
        Vector3 _point;
        Vector3 _normal;

    public:
        IntersectionData() = default;
        IntersectionData(float distance, const Vector3& point, const Vector3& normal);

        float GetDistance() const;
        void SetDistance(float distance);

        Vector3 GetPoint() const;
        void SetPoint(const Vector3& point);

        Vector3 GetNormal() const;
        void SetNormal(const Vector3& normal);
    };
}