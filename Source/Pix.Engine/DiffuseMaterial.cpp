#include "DiffuseMaterial.h"

using namespace Pix::Engine::Materials;

DiffuseMaterial::DiffuseMaterial(const Color3 & color, float diffuseWeight, float specularWeight)
    : Material(MaterialType::Diffuse), Color(color), DiffuseWeight(diffuseWeight), SpecularWeight(specularWeight)
{

}