#include "GeometryGroup.h"

using namespace Pix::Base;
using namespace Pix::Base::Geometries;

GeometryGroup::GeometryGroup(const std::vector<const Geometry*>* geometries)
    : _geometries(geometries)
{

}

float GeometryGroup::IntersectRay(const Ray& ray, const Geometry** hitGeometry) const
{
    auto closestDistance = INFINITY;
    const Geometry* closestGeometry = nullptr;

    for (const auto& geometry : *_geometries)
    {
        const Geometry* foundGeometry;
        auto foundDistance = geometry->IntersectRay(ray, &foundGeometry);

        if (foundDistance < closestDistance)
        {
            closestDistance = foundDistance;
            closestGeometry = foundGeometry;
        }
    }

    *hitGeometry = closestGeometry;
    return closestDistance;
}

void GeometryGroup::GetIntersectionData(const Ray& ray, float distance, IntersectionData* intersectionData) const
{

}