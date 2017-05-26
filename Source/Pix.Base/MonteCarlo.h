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
            float sinTheta = sqrtf(1 - random1 * random1);
            float phi = 2 * 3.14159f * random2;

            float x = sinTheta * cosf(phi);
            float z = sinTheta * sinf(phi);
        
            return Vector3(x, random1, z);
        }
    };
}