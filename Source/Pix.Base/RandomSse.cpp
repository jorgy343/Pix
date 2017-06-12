#include "RandomSse.h"

#include <random>
#include <nmmintrin.h>
#include <emmintrin.h>

using namespace Pix::Base;

RandomSse::RandomSse()
{
    std::random_device randomDevice{ };

    _x[0] = randomDevice();
    _x[1] = randomDevice();
    _x[2] = randomDevice();
    _x[3] = randomDevice();

    _y[0] = randomDevice();
    _y[1] = randomDevice();
    _y[2] = randomDevice();
    _y[3] = randomDevice();
}

RandomSse::RandomSse(
    uint32_t random1,
    uint32_t random2,
    uint32_t random3,
    uint32_t random4,
    uint32_t random5,
    uint32_t random6,
    uint32_t random7,
    uint32_t random8)
{
    _x[0] = random1;
    _x[1] = random2;
    _x[2] = random3;
    _x[3] = random4;

    _y[0] = random5;
    _y[1] = random6;
    _y[2] = random7;
    _y[3] = random8;
}

void RandomSse::GetNextInteger(uint32_t* result)
{
    const __m128i a = _mm_set1_epi32(18000);
    const __m128i b = _mm_set1_epi32(30903);

    __m128i x = _mm_load_si128((__m128i*)_x);
    __m128i y = _mm_load_si128((__m128i*)_y);

    __m128i xMask = _mm_and_si128(x, _mm_set1_epi32(0xffff));
    __m128i xMul = _mm_mullo_epi32(a, xMask);
    __m128i xShift = _mm_srli_epi32(x, 16);

    x = _mm_add_epi32(xMul, xShift);
    _mm_store_si128((__m128i*)_x, x);

    __m128i yMask = _mm_and_si128(y, _mm_set1_epi32(0xffff));
    __m128i yMul = _mm_mullo_epi32(b, yMask);
    __m128i yShift = _mm_srli_epi32(y, 16);

    y = _mm_add_epi32(yMul, yShift);
    _mm_store_si128((__m128i*)_y, y);

    __m128i xResult = _mm_slli_epi32(x, 16);
    __m128i yResult = _mm_and_si128(y, _mm_set1_epi32(0xffff));
    __m128i xResultPlusYResult = _mm_add_epi32(xResult, yResult);

    _mm_store_si128((__m128i*)result, xResultPlusYResult);
}

void RandomSse::GetNextFloat(float* result)
{
    const __m128i a = _mm_set1_epi32(18000);
    const __m128i b = _mm_set1_epi32(30903);

    __m128i x = _mm_load_si128((__m128i*)_x);
    __m128i y = _mm_load_si128((__m128i*)_y);

    __m128i xMask = _mm_and_si128(x, _mm_set1_epi32(0xffff));
    __m128i xMul = _mm_mullo_epi32(a, xMask);
    __m128i xShift = _mm_srli_epi32(x, 16);

    x = _mm_add_epi32(xMul, xShift);
    _mm_store_si128((__m128i*)_x, x);

    __m128i yMask = _mm_and_si128(y, _mm_set1_epi32(0xffff));
    __m128i yMul = _mm_mullo_epi32(b, yMask);
    __m128i yShift = _mm_srli_epi32(y, 16);

    y = _mm_add_epi32(yMul, yShift);
    _mm_store_si128((__m128i*)_y, y);

    __m128i xResult = _mm_slli_epi32(x, 16);
    __m128i yResult = _mm_and_si128(y, _mm_set1_epi32(0xffff));
    __m128i xResultPlusYResult = _mm_add_epi32(xResult, yResult);

    __m128i floatResultMantissa = _mm_and_si128(xResultPlusYResult, _mm_set1_epi32(0x3F'FFFF));
    __m128i floatExponentSet = _mm_or_si128(floatResultMantissa, _mm_set1_epi32(0x4000'0000));

    __m128 floatResult = _mm_castsi128_ps(floatExponentSet);
    floatResult = _mm_sub_ps(floatResult, _mm_set1_ps(2.0f));

    _mm_store_ps(result, floatResult);
}