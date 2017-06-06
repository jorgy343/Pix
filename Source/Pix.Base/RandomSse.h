#pragma once

#include <stdint.h>
#include <nmmintrin.h>
#include <emmintrin.h>

namespace Pix::Base
{
    class RandomSse
    {
    private:
        __declspec(align(16)) uint32_t _a[4];
        __declspec(align(16)) uint32_t _b[4];

        __declspec(align(16)) uint32_t _x[4];
        __declspec(align(16)) uint32_t _y[4];

        __declspec(align(16)) uint32_t _mask[4];

        __declspec(align(16)) uint32_t _floatMantissaMask[4];
        __declspec(align(16)) uint32_t _floatExponent[4];
        __declspec(align(16)) float _floatSubtract[4];

    public:
        RandomSse(
            uint32_t random1,
            uint32_t random2,
            uint32_t random3,
            uint32_t random4,
            uint32_t random5,
            uint32_t random6,
            uint32_t random7,
            uint32_t random8)
        {
            _a[0] = 18000;
            _a[1] = 18000;
            _a[2] = 18000;
            _a[3] = 18000;

            _b[0] = 30903;
            _b[1] = 30903;
            _b[2] = 30903;
            _b[3] = 30903;

            _x[0] = random1;
            _x[1] = random2;
            _x[2] = random3;
            _x[3] = random4;

            _y[0] = random5;
            _y[1] = random6;
            _y[2] = random7;
            _y[3] = random8;

            _mask[0] = 0xffff;
            _mask[1] = 0xffff;
            _mask[2] = 0xffff;
            _mask[3] = 0xffff;

            _floatMantissaMask[0] = 0x3F'FFFF;
            _floatMantissaMask[1] = 0x3F'FFFF;
            _floatMantissaMask[2] = 0x3F'FFFF;
            _floatMantissaMask[3] = 0x3F'FFFF;

            _floatExponent[0] = 0x4000'0000;
            _floatExponent[1] = 0x4000'0000;
            _floatExponent[2] = 0x4000'0000;
            _floatExponent[3] = 0x4000'0000;

            _floatSubtract[0] = 2.0f;
            _floatSubtract[1] = 2.0f;
            _floatSubtract[2] = 2.0f;
            _floatSubtract[3] = 2.0f;
        }

        inline void GetNextInteger(uint32_t* result)
        {
            const __m128i a = _mm_load_si128((__m128i*)_a);
            const __m128i b = _mm_load_si128((__m128i*)_b);

            __m128i x = _mm_load_si128((__m128i*)_x);
            __m128i y = _mm_load_si128((__m128i*)_y);

            const __m128i mask = _mm_load_si128((__m128i*)_mask);

            __m128i xMask = _mm_and_si128(x, mask);
            __m128i xMul = _mm_mullo_epi32(a, xMask);
            __m128i xShift = _mm_srli_epi32(x, 16);

            x = _mm_add_epi32(xMul, xShift);
            _mm_store_si128((__m128i*)_x, x);

            __m128i yMask = _mm_and_si128(y, mask);
            __m128i yMul = _mm_mullo_epi32(b, yMask);
            __m128i yShift = _mm_srli_epi32(y, 16);

            y = _mm_add_epi32(yMul, yShift);
            _mm_store_si128((__m128i*)_y, y);

            __m128i xResult = _mm_slli_epi32(x, 16);
            __m128i yResult = _mm_and_si128(y, mask);
            __m128i xResultPlusYResult = _mm_add_epi32(xResult, yResult);

            _mm_store_si128((__m128i*)result, xResultPlusYResult);
        }

        inline void GetNextFloat(float* result)
        {
            const __m128i a = _mm_load_si128((__m128i*)_a);
            const __m128i b = _mm_load_si128((__m128i*)_b);

            __m128i x = _mm_load_si128((__m128i*)_x);
            __m128i y = _mm_load_si128((__m128i*)_y);

            const __m128i mask = _mm_load_si128((__m128i*)_mask);

            const __m128i floatMantissaMask = _mm_load_si128((__m128i*)_floatMantissaMask);
            const __m128i floatExponent = _mm_load_si128((__m128i*)_floatExponent);
            const __m128 floatSubtract = _mm_load_ps(_floatSubtract);

            __m128i xMask = _mm_and_si128(x, mask);
            __m128i xMul = _mm_mullo_epi32(a, xMask);
            __m128i xShift = _mm_srli_epi32(x, 16);

            x = _mm_add_epi32(xMul, xShift);
            _mm_store_si128((__m128i*)_x, x);

            __m128i yMask = _mm_and_si128(y, mask);
            __m128i yMul = _mm_mullo_epi32(b, yMask);
            __m128i yShift = _mm_srli_epi32(y, 16);

            y = _mm_add_epi32(yMul, yShift);
            _mm_store_si128((__m128i*)_y, y);

            __m128i xResult = _mm_slli_epi32(x, 16);
            __m128i yResult = _mm_and_si128(y, mask);
            __m128i xResultPlusYResult = _mm_add_epi32(xResult, yResult);

            __m128i floatResultMantissa = _mm_and_si128(xResultPlusYResult, floatMantissaMask);
            __m128i floatExponentSet = _mm_or_si128(floatResultMantissa, floatExponent);

            __m128 floatResult = _mm_castsi128_ps(floatExponentSet);
            floatResult = _mm_sub_ps(floatResult, floatSubtract);

            _mm_store_ps(result, floatResult);
        }
    };
}