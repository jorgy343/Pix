#pragma once

#include "Matrix33T.h"

namespace Pix::Base
{
    typedef __declspec(align(16)) Matrix33T<float> Matrix33;
}