#include "MonteCarlo.h"

#include <nmmintrin.h>
#include "SseFunctions.h"

namespace Pix::Base
{
    Vector3 MonteCarlo::CosineWeightedSampleHemisphere(float random1, float random2)
    {
        float r = std::sqrtf(random1);
        float theta = TwoPi<float> * random2;

        float x = r * std::cosf(theta);
        float z = r * std::sinf(theta);

        return Vector3(x, std::sqrtf(std::max<float>(0.0f, 1.0f - random1)), z);
    }

    void MonteCarlo::CosineWeightedSampleHemisphere4(Vector3* _samples, const float* _random1, const float* _random2)
    {
        __m128 zero = _mm_setzero_ps();

        const float _one = 1.0f;
        __m128 one = _mm_load_ps1(&_one);

        const float _twoPi = 6.283185307179586476925286766559005768394338798750211641949f;
        __m128 twoPi = _mm_load_ps1(&TwoPi<float>);

        __m128 random1 = _mm_load_ps(_random1);
        __m128 random2 = _mm_load_ps(_random2);

        __m128 r = _mm_sqrt_ps(random1);
        __m128 theta = _mm_mul_ps(twoPi, random2);

        __m128 x;
        __m128 z;

        sincos_ps(theta, &z, &x);

        x = _mm_mul_ps(x, r);
        z = _mm_mul_ps(z, r);

        __m128 oneMinusRandom1 = _mm_sub_ps(one, random1);
        __m128 y = _mm_max_ps(zero, oneMinusRandom1);
        y = _mm_sqrt_ps(y);

        float samplesX[4];
        float samplesY[4];
        float samplesZ[4];

        _mm_store_ps(samplesX, x);
        _mm_store_ps(samplesY, y);
        _mm_store_ps(samplesZ, z);

        _samples[0].X = samplesX[0];
        _samples[1].X = samplesX[1];
        _samples[2].X = samplesX[2];
        _samples[3].X = samplesX[3];

        _samples[0].Y = samplesY[0];
        _samples[1].Y = samplesY[1];
        _samples[2].Y = samplesY[2];
        _samples[3].Y = samplesY[3];

        _samples[0].Z = samplesZ[0];
        _samples[1].Z = samplesZ[1];
        _samples[2].Z = samplesZ[2];
        _samples[3].Z = samplesZ[3];
    }
}