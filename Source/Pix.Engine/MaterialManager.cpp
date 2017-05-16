#include "MaterialManager.h"

using namespace Pix::Engine::Materials;

MaterialManager::MaterialManager(const MaterialGeometryMap* map)
    : _map(map)
{

}

const Material* MaterialManager::GetMaterialForGeometry(const Geometry* geometry) const
{
    auto item = _map->find(geometry);
    return item == _map->end() ? nullptr : item->second;
}