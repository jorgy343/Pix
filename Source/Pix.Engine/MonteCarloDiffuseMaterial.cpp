#include "MonteCarloDiffuseMaterial.h"

using namespace Pix::Engine::Materials;

MonteCarloDiffuseMaterial::MonteCarloDiffuseMaterial(const Color3 & color)
    : Material(MaterialType::MonteCarloDiffuse), Color(color)
{

}