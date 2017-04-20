#pragma once

#include "MatrixT.h"

namespace Pix::Base
{
    typedef __declspec(align(16)) MatrixT<float> Matrix;
}