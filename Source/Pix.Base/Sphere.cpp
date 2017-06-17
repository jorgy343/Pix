#include "Sphere.h"

using namespace Pix::Base;
using namespace Pix::Base::Geometries;

Sphere::Sphere(Vector3 position, float radius)
    : Position(position), Radius(radius)
{
    
}

float Sphere::IntersectRay(const Ray& ray, const Geometry** hitGeometry) const
{
    // ‖x − c‖² = r²                    Equation of sphere
    // x = s + td                       Equation of ray
    // 
    // ‖s + td - c‖² = r²               Substitute equation of ray into equation of sphere.
    // v ≝ s − c
    // ‖v + td‖² = r²
    // v² + 2t(v⋅d) + t²d² = r²         Expand binomial.
    // t²d² + 2t(v⋅d) + v² - r² = 0
    // 
    // a = d², b = 2(v⋅d), c = v² - r²
    // (-b ± √(b² - 4ac)) / (2a)        Quadratic equation.
    // 
    // t = (-2(v⋅d) ± √((2(v⋅d))² - 4d²(v² - r²))) / (2d²)
    // t = (-(v⋅d) ± √((v⋅d)² - d²(v² - r²))) / d²
    // 
    // Discriminant is
    // (v⋅d)² - d²(v² - r²)
    // 
    // Entrance of intersection
    // (-(v⋅d) + √((v⋅d)² - d²(v² - r²))) / d²
    // 
    // Exit of intersection
    // (-(v⋅d) - √((v⋅d)² - d²(v² - r²))) / d²

    Vector3 v = ray.Position - Position;
    float vDotd = Vector3::Dot(v, ray.Direction);
    float vDotdSquared = vDotd * vDotd;

    float dSquared = Vector3::Dot(ray.Direction, ray.Direction);
    float vSquared = Vector3::Dot(v, v);
    float rSquared = Radius * Radius;

    float discriminant = vDotdSquared - dSquared * (vSquared - rSquared);
    if (discriminant < Epsilon)
        return INFINITY;

    float discriminantSquareRoot = sqrt(discriminant);
    float vDotdNegative = -vDotd;

    float exitDistance = (vDotdNegative + discriminantSquareRoot) / dSquared;
    if (exitDistance < Epsilon)
        return INFINITY;

    *hitGeometry = this;
    return fmax((vDotdNegative - discriminantSquareRoot) / dSquared, 0.0f);
}

void Sphere::GetIntersectionData(const Ray& ray, float distance, IntersectionData* intersectionData) const
{
    Vector3 point = ray.Position + distance * ray.Direction;
    Vector3 normal = (point - Position) / Radius;

    intersectionData->IntersectedGeometry = this;
    intersectionData->Distance = distance;
    intersectionData->Point = point;
    intersectionData->Normal = normal;
}