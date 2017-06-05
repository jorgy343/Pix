#include "IntersectionData.h"

using namespace Pix::Base;
using namespace Pix::Base::Geometries;

Pix::Base::IntersectionData::IntersectionData(const Geometry* intersectedGeometry, float distance, const Vector3& point, const Vector3& normal)
    : IntersectedGeometry(intersectedGeometry), Distance(distance), Point(point), Normal(normal)
{

}