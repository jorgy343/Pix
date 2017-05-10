#include "SceneOptions.h"

using namespace Pix::Engine;

SceneOptions::SceneOptions(const Color3& defaultColor, int antialiasingLevel)
    : _defaultColor(defaultColor), _antialiasingLevel(antialiasingLevel)
{

}

Color3 SceneOptions::GetDefaultColor() const
{
    return _defaultColor;
}

int SceneOptions::GetAntialiasingLevel() const
{
    return _antialiasingLevel;
}