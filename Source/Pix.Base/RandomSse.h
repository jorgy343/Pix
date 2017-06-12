#pragma once

#include <stdint.h>

namespace Pix::Base
{
    class RandomSse
    {
    private:
        __declspec(align(16)) uint32_t _x[4];
        __declspec(align(16)) uint32_t _y[4];

    public:
        RandomSse();
        RandomSse(
            uint32_t random1,
            uint32_t random2,
            uint32_t random3,
            uint32_t random4,
            uint32_t random5,
            uint32_t random6,
            uint32_t random7,
            uint32_t random8);

        void GetNextInteger(uint32_t* result);
        void GetNextFloat(float* result);
    };
}