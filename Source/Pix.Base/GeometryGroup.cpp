#include "GeometryGroup.h"

using namespace Pix::Base;
using namespace Pix::Base::Geometries;

GeometryGroup::GeometryGroup(const std::vector<const Geometry*>* geometries)
    : _geometries(geometries)
{

}

float GeometryGroup::IntersectRay(const Ray& ray, const Geometry** hitGeometry) const
{
    auto closestDistance = FLT_MAX;
    const Geometry* closestGeometry = nullptr;

    for (const auto& geometry : *_geometries)
    {
        const Geometry* tempGeometry;
        auto foundDistance = geometry->IntersectRay(ray, &tempGeometry);

        if (foundDistance != INFINITY && foundDistance < closestDistance)
        {
            closestDistance = foundDistance;
            closestGeometry = tempGeometry;
        }
    }

    *hitGeometry = closestGeometry;
    return closestDistance == FLT_MAX ? INFINITY : closestDistance;
}

void GeometryGroup::GetIntersectionData(const Ray& ray, float distance, IntersectionData* intersectionData) const
{

}