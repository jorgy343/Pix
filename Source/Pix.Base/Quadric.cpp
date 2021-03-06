#include "Quadric.h"

using namespace Pix::Base;
using namespace Pix::Base::Geometries;

Quadric::Quadric(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j)
    : A(a), B(b), C(c), D(d), E(e), F(f), G(g), H(h), I(i), J(j)
{

}

float Quadric::IntersectRay(const Ray& ray, const Geometry** hitGeometry) const
{
    Matrix44 Q(
        A, B, C, D,
        B, E, F, G,
        C, F, H, I,
        D, G, I, J);

    Vector4 s(ray.Position.X, ray.Position.Y, ray.Position.Z, 1.0f);
    Vector4 d(ray.Direction.X, ray.Direction.Y, ray.Direction.Z, 0.0f);

    Vector4 qs = s * Q;
    Vector4 qd = d * Q;

    float a = Vector4::Dot(d, qd);
    float b = Vector4::Dot(s, qd) + Vector4::Dot(d, qs);
    float c = Vector4::Dot(s, qs);

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant < 0.0f)
        return INFINITY;

    float distance = (-b - sqrt(discriminant)) / (2.0f * a);
    if (distance < 0.0f)
        return INFINITY;

    *hitGeometry = this;
    return distance;
}

void Quadric::GetIntersectionData(const Ray& ray, float distance, IntersectionData* intersectionData) const
{
    Matrix44 Q(
        A, B, C, D,
        B, E, F, G,
        C, F, H, I,
        D, G, I, J);

    Vector3 point = ray.Position + distance * ray.Direction;
    Vector4 point4(point.X, point.Y, point.Z, 1.0f);

    Vector4 normal4 = point4 * Q;
    Vector3 normal = Vector3(normal4.X, normal4.Y, normal4.Z).Normalize();

    intersectionData->IntersectedGeometry = this;
    intersectionData->Distance = distance;
    intersectionData->Point = point;
    intersectionData->Normal = normal;
}