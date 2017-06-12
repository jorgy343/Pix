#include "MonteCarlo.h"

#include <nmmintrin.h>
#include "SseFunctions.h"

namespace Pix::Base
{
    void MonteCarlo::CreateTangentCoordinateSystem(const Vector3& normal, Vector3* normalTangent, Vector3* normalBitangent)
    {
        if (std::fabs(normal.X) > std::fabs(normal.Y))
            *normalTangent = Vector3(normal.Z, 0, -normal.X).Normalize();
        else
            *normalTangent = Vector3(0, -normal.Z, normal.Y).Normalize();

        *normalBitangent = Vector3::CrossProduct(normal, *normalTangent);
    }

    Vector3 MonteCarlo::UniformSampleHemisphere(float random1, float random2)
    {
        float sinTheta = sqrtf(1.0f - random1 * random1);
        float phi = TwoPi<float> * random2;

        float x = sinTheta * cosf(phi);
        float z = sinTheta * sinf(phi);

        return Vector3(x, random1, z);
    }

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
        __m128 random1 = _mm_load_ps(_random1);
        __m128 random2 = _mm_load_ps(_random2);

        __m128 r = _mm_sqrt_ps(random1);
        __m128 theta = _mm_mul_ps(_mm_set1_ps(TwoPi<float>), random2);

        __m128 x;
        __m128 z;

        SinCos(theta, &z, &x);

        x = _mm_mul_ps(x, r);
        z = _mm_mul_ps(z, r);

        __m128 oneMinusRandom1 = _mm_sub_ps(_mm_set1_ps(1.0f), random1);
        __m128 y = _mm_max_ps(_mm_setzero_ps(), oneMinusRandom1);
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

    Ray MonteCarlo::WeirdThingThatMightWork(const Vector3& position, const Vector3& normal, float random1, float random2)
    {
        float theta = TwoPi<float> * random1;
        float r = sqrt(random2);

        Vector3 w = normal;
        Vector3 u = (Vector3::CrossProduct((fabs(Vector3::Dot(w, position)) > Epsilon ? Vector3(0.0f, 1.0f, 0.0f) : Vector3(1.0f)), w)).Normalize();
        Vector3 v = Vector3::CrossProduct(w, u);

        Vector3 d = (u * cos(theta) * r + v * sin(theta) * r + w * std::sqrtf(1.0f - random2)).Normalize();
        return Ray(position, d);
    }
}