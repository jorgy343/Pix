#pragma once

#include <math.h>

#include "Vector3.h"
#include "Ray.h"
#include "General.h"

namespace Pix::Base
{
    class MonteCarlo
    {
    public:
        static void CreateTangentCoordinateSystem(const Vector3& normal, Vector3* normalTangent, Vector3* normalBitangent);
        static Vector3 UniformSampleHemisphere(float random1, float random2);

        static Vector3 CosineWeightedSampleHemisphere(float random1, float random2);
        static void CosineWeightedSampleHemisphere4(Vector3* samples, const float* random1, const float* random2);

        static Ray WeirdThingThatMightWork(const Vector3& position, const Vector3& normal, float random1, float random2);
    };
}