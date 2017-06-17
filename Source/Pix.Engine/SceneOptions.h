#pragma once

#include "Color3.h"

using namespace Pix::Base;

namespace Pix::Engine
{
    class SceneOptions
    {
    private:
        int _maxDepth;
        Color3 _defaultColor;
        int _antialiasingLevel;
        int _russianRouletteDepthStart;
        float _russianRouletteStopFactor;

    public:
        SceneOptions(int maxDepth, const Color3& defaultColor, int antialiasingLevel, int russianRouletteDepthStart, float russianRouletteStopFactor);

        int GetMaxDepth() const;
        Color3 GetDefaultColor() const;
        int GetAntialiasingLevel() const;
        int GetRussianRouletteDepthStart() const;
        float GetRussianRouletteStopFactor() const;
    };
}