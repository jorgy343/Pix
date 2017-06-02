#include "SceneOptions.h"

using namespace Pix::Engine;

SceneOptions::SceneOptions(int maxDepth, const Color3& defaultColor, int antialiasingLevel)
    : _maxDepth(maxDepth), _defaultColor(defaultColor), _antialiasingLevel(antialiasingLevel)
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