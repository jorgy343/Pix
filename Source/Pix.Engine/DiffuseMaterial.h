#pragma once

#include "Material.h"
#include "Color3.h"

using namespace Pix::Base;

namespace Pix::Engine::Materials
{
    class DiffuseMaterial : public Material
    {
    public:
        Color3 Color;
        float DiffuseWeight;
        float SpecularWeight;

        DiffuseMaterial(const Color3& color, float diffuseWeight, float specularWeight);
    };
}