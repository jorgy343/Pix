#pragma once

#include "Material.h"
#include "Color3.h"

using namespace Pix::Base;

namespace Pix::Engine::Materials
{
    class MonteCarloDiffuseMaterial : public Material
    {
    public:
        Color3 Color;

        MonteCarloDiffuseMaterial(const Color3& color);
    };
}