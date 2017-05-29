#pragma once

#include <functional>

#include "Color3.h"
#include "IntersectionData.h"

namespace Pix::Base
{
    const float Epsilon = 0.1f;

    template <typename T>
    constexpr T Pi = T(3.141592653589793238462643383279502884197169399375105820974);

    template <typename T>
    constexpr T TwoPi = T(6.283185307179586476925286766559005768394338798750211641949);

    template <typename T>
    constexpr T OneOverPi = T(0.318309886183790671537767526745028724068919291480912897495);

    template <typename T>
    constexpr T OneOverTwoPi = T(0.159154943091895335768883763372514362034459645740456448747);
}