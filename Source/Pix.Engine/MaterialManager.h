#pragma once

#include "Geometry.h"
#include "MaterialAliases.h"

using namespace Pix::Base::Geometries;

namespace Pix::Engine::Materials
{
    class MaterialManager
    {
    private:
        const MaterialGeometryMap* _map;

    public:
        MaterialManager(const MaterialGeometryMap* map);

        const Material* GetMaterialForGeometry(const Geometry* geometry) const;
    };
}