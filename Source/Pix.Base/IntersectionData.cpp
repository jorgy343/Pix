#include "IntersectionData.h"

using namespace Pix::Base;

IntersectionData::IntersectionData(float distance, const Vector3& point, const Vector3& normal)
    : _distance(distance), _point(point), _normal(normal)
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