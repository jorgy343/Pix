﻿#include "Plane.h"

using namespace Pix::Base;
using namespace Pix::Base::Geometries;

Plane::Plane(Vector3 normal, float d)
    : Normal(normal), D(d)
{

}


Plane::Plane(Vector3 normal, Vector3 point)
    : Normal(normal), D(-Vector3::Dot(normal, point))
{

}

float Plane::IntersectRay(const Ray& ray, const Geometry** hitGeometry) const
{
    // x₀ = s + td              Equation of ray
    // N + D = 0                Equation of plane
    // 
    // Ax + By + Cz + D = 0                                 Expand equation of plane.
    // A(sx + tdx) + B(sy + tdy) + C(sz + tdz) + D = 0      Substitute equation of ray into equation of plane.
    // 
    // Solve for t
    // Asx + Atdx + Bsy + Btdy + Csz + Ctdz + D = 0
    // Asx + Atdx + Bsy + Btdy + Csz + Ctdz = -D
    // (Atdx + Btdy + Ctdz) + (Asx + Bsy + Csz) = -D
    // t(Adx + Bdy + Cdz) + (Asx + Bsy + Csz) = -D
    // t(Adx + Bdy + Cdz) = -D - Asx - Bsy - Csz
    // t(Adx + Bdy + Cdz) = -(D + Asx + Bsy + Csz)
    // t = -(D + Asx + Bsy + Csz) / (Adx + Bdy + Cdz)
    // t = -(D + N⋅s) / (N⋅d)                               Contract previous expansions.
    // 
    // If denominator is zero, ray is parallel and no intersection occurs. If the ray lies exactly inside the
    // plane, it is considered that no intersection occured.

    float nDotD = Vector3::Dot(Normal, ray.Direction);

    // Assume this will never happen.
    //if (nDotD == 0.0f)
    //    return INFINITY;

    float nDotS = Vector3::Dot(Normal, ray.Position);
    float distance = -(D + nDotS) / nDotD;

    if (distance < 0.0f)
        return INFINITY;

    *hitGeometry = this;
    return distance;
}


void Plane::GetIntersectionData(const Ray& ray, float distance, IntersectionData* intersectionData) const
{
    Vector3 point = ray.Position + distance * ray.Direction;

    intersectionData->IntersectedGeometry = this;
    intersectionData->Distance = distance;
    intersectionData->Point = point;
    intersectionData->Normal = Normal;
}