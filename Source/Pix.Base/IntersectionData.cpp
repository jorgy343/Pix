#include "IntersectionData.h"

using namespace Pix::Base;
using namespace Pix::Base::Geometries;

Pix::Base::IntersectionData::IntersectionData(const Geometry* intersectedGeometry, float distance, const Vector3& point, const Vector3& normal)
    : _intersectedGeometry(intersectedGeometry), _distance(distance), _point(point), _normal(normal)
{

}

float IntersectionData::GetDistance() const
{
    return _distance;
}

void IntersectionData::SetDistance(float distance)
{
    _distance = distance;
}

Vector3 IntersectionData::GetPoint() const
{
    return _point;
}

void IntersectionData::SetPoint(const Vector3& point)
{
    _point = point;
}

Vector3 IntersectionData::GetNormal() const
{
    return _normal;
}

void IntersectionData::SetNormal(const Vector3& normal)
{
    _normal = normal;
}