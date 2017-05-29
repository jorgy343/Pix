#pragma once

#include "Vector3.h"

namespace Pix::Base
{
    class MonteCarlo
    {
    public:
        static void CreateTangentCoordinateSystem(const Vector3& normal, Vector3* normalTangent, Vector3* normalBitangent)
        {
            if (std::fabs(normal.X) > std::fabs(normal.Y))
                *normalTangent = Vector3(normal.Z, 0, -normal.X).Normalize();
            else
                *normalTangent = Vector3(0, -normal.Z, normal.Y).Normalize();

            *normalBitangent = Vector3::CrossProduct(normal, *normalTangent);
        }

        static Vector3 UniformSampleHemisphere(float random1, float random2)
        {
            float sinTheta = sqrtf(1.0f - random1 * random1);
            float phi = 2.0f * Pi<float> * random2;

            float x = sinTheta * cosf(phi);
            float z = sinTheta * sinf(phi);
        
            return Vector3(x, random1, z);
        }

        static Vector3 CosineWeightedSampleHemisphere(float random1, float random2)
        {
            float r = std::sqrtf(random1);
            float theta = 2.0f * Pi<float> * random2;

            float x = r * std::cosf(theta);
            float z = r * std::sinf(theta);

            return Vector3(x, std::sqrtf(std::max<float>(0.0f, 1.0f - random1)), z);
        }
    };
}