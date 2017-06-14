#include "MonteCarloDiffuseMaterial.h"

using namespace Pix::Engine::Materials;

MonteCarloDiffuseMaterial::MonteCarloDiffuseMaterial(const Color3& color, const Color3& emissiveColor)
    : Material(MaterialType::MonteCarloDiffuse), Color(color), EmissiveColor(emissiveColor)
{

}