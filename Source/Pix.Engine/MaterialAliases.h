#pragma once

#include <map>

#include "Geometry.h"
#include "Material.h"

using namespace Pix::Base::Geometries;

namespace Pix::Engine::Materials
{
    using MaterialNameMap = std::map<std::string, const Material*>;
    using MaterialGeometryMap = std::map<const Geometry*, const Material*>;
}