#include "IntersectionData.h"

using namespace Pix::Base;
using namespace Pix::Base::Geometries;

Pix::Base::IntersectionData::IntersectionData(const Geometry* intersectedGeometry, float distance, const Vector3& point, const Vector3& normal)
    : _intersectedGeometry(intersectedGeometry), _distance(distance), _point(point), _normal(normal)
{

}

const Geometry* IntersectionData::GetIntersectedGeometry() const
{
    return _intersectedGeometry;
}

float IntersectionData::GetDistance() const
{
    return _distance;
}

Vector3 IntersectionData::GetPoint() const
{
    return _point;
}

Vector3 IntersectionData::GetNormal() const
{
    return _normal;
}