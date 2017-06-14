#pragma once

#include "Material.h"
#include "Color3.h"

using namespace Pix::Base;

namespace Pix::Engine::Materials
{
    class PhongDiffuseMaterial : public Material
    {
    public:
        Color3 AmbientColor;
        Color3 DiffuseColor;
        float DiffuseCoefficient;

        PhongDiffuseMaterial(const Color3& ambientColor, const Color3& diffuseColor, float diffuseCoefficient);
    };
}