#include "GeometryGroup.h"

using namespace Pix::Base;
using namespace Pix::Base::Geometries;

GeometryGroup::GeometryGroup(const std::vector<const Geometry*>* geometries)
    : _geometries(geometries)
{

}

float GeometryGroup::IntersectRay(const Ray& ray, IntersectionData* intersectionData) const
{
    auto closestDistance = FLT_MAX;
    IntersectionData tempIntersectionData;

    for (const auto& surface : *_geometries)
    {
        auto foundDistance = surface->IntersectRay(ray, &tempIntersectionData);
        if (foundDistance != INFINITY && foundDistance < closestDistance)
        {
            closestDistance = foundDistance;
            if (intersectionData != nullptr)
                *intersectionData = tempIntersectionData; // TODO: Only set intersectionData at the end instead of every time we find a closer object.
        }
    }

    return closestDistance == FLT_MAX ? INFINITY : closestDistance;
}