#pragma once

#include "MaterialType.h"

namespace Pix::Engine::Materials
{
    class Material
    {
    public:
        MaterialType Type;

        explicit Material(MaterialType type);
    };
}