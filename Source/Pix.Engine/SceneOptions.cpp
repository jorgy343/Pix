#include "SceneOptions.h"

using namespace Pix::Engine;

SceneOptions::SceneOptions(int maxDepth, const Color3& defaultColor, int antialiasingLevel, int russianRouletteDepthStart, float russianRouletteStopFactor)
    : _maxDepth(maxDepth), _defaultColor(defaultColor), _antialiasingLevel(antialiasingLevel), _russianRouletteDepthStart(russianRouletteDepthStart), _russianRouletteStopFactor(russianRouletteStopFactor)
{

}

int SceneOptions::GetMaxDepth() const
{
    return _maxDepth;
}

Color3 SceneOptions::GetDefaultColor() const
{
    return _defaultColor;
}

int SceneOptions::GetAntialiasingLevel() const
{
    return _antialiasingLevel;
}

int SceneOptions::GetRussianRouletteDepthStart() const
{
    return _russianRouletteDepthStart;
}

float SceneOptions::GetRussianRouletteStopFactor() const
{
    return _russianRouletteStopFactor;
}