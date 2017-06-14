#include "PhongDiffuseMaterial.h"

using namespace Pix::Engine::Materials;

PhongDiffuseMaterial::PhongDiffuseMaterial(const Color3& ambientColor, const Color3& diffuseColor, float diffuseCoefficient)
    : Material(MaterialType::PhongDiffuse), AmbientColor(ambientColor), DiffuseColor(diffuseColor), DiffuseCoefficient(diffuseCoefficient)
{

}