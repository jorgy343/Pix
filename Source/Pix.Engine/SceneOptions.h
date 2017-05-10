#pragma once

#include "Color3.h"

using namespace Pix::Base;

namespace Pix::Engine
{
    class SceneOptions
    {
    private:
        Color3 _defaultColor;
        int _antialiasingLevel;

    public:
        SceneOptions(const Color3& defaultColor, int antialiasingLevel);

        Color3 GetDefaultColor() const;
        int GetAntialiasingLevel() const;
    };
}