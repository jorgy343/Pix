#include "Sphere.h"

using namespace Pix::Base;
using namespace Pix::Base::Geometries;

Sphere::Sphere(Vector3 position, float radius)
    : Position(position), Radius(radius)
{

}

const Geometry* Sphere::IntersectRay(const Ray& ray, IntersectionData* intersectionData) const
{
    Vector3 v = ray.Position - Position;
    float vDotd = Vector3::Dot(v, ray.Direction);
    float vDotdSquared = vDotd * vDotd;

    float dSquared = Vector3::Dot(ray.Direction, ray.Direction);
    float vSquared = Vector3::Dot(v, v);
    float rSquared = Radius * Radius;

    float discriminant = vDotdSquared - dSquared * (vSquared - rSquared);
    if (discriminant < Epsilon)
        return nullptr;

    float discriminantSquareRoot = sqrt(discriminant);
    float vDotdNegative = -vDotd;

    float exitDistance = (vDotdNegative + discriminantSquareRoot) / dSquared;
    if (exitDistance < Epsilon)
        return nullptr;

    float entranceDistance = fmax((vDotdNegative - discriminantSquareRoot) / dSquared, 0.0f);

    Vector3 point = ray.Position + entranceDistance * ray.Direction;
    Vector3 normal = (point - Position).Normalize();

    *intersectionData = IntersectionData(entranceDistance, point, normal);
    return this;
}