#pragma once

#include "Matrix44T.h"

namespace Pix::Base
{
    typedef __declspec(align(16)) Matrix44T<float> Matrix44;
}