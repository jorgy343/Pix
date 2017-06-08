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
            float phi = TwoPi<float> * random2;

            float x = sinTheta * cosf(phi);
            float z = sinTheta * sinf(phi);
            
            return Vector3(x, random1, z);
        }

        static Vector3 CosineWeightedSampleHemisphere(float random1, float random2);
        static void CosineWeightedSampleHemisphere4(Vector3* samples, const float* random1, const float* random2);

        static Ray WeirdThingThatMightWork(const Vector3& position, const Vector3& normal, float random1, float random2)
        {
            float theta = TwoPi<float> * random1;
            float r = sqrt(random2);

            Vector3 w = normal;
            Vector3 u = (Vector3::CrossProduct((fabs(Vector3::Dot(w, position)) > Epsilon ? Vector3(0.0f, 1.0f, 0.0f) : Vector3(1.0f)), w)).Normalize();
            Vector3 v = Vector3::CrossProduct(w, u);

            Vector3 d = (u * cos(theta) * r + v * sin(theta) * r + w * std::sqrtf(1.0f - random2)).Normalize();
            return Ray(position, d);
        }
    };
}