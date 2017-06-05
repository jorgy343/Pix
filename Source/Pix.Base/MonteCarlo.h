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
            float phi = 2.0f * Pi<float> * random2;

            float x = sinTheta * cosf(phi);
            float z = sinTheta * sinf(phi);
            
            return Vector3(x, random1, z);
        }

        static __declspec(noinline) Vector3 CosineWeightedSampleHemisphere(float random1, float random2);
        static __declspec(noinline) void CosineWeightedSampleHemisphere4(Vector3* samples, const float* random1, const float* random2);

        static Ray WeirdThingThatMightWork(const Vector3& position, const Vector3& normal, float random1, float random2)
        {
            float theta = 2.0f * Pi<float> * random1;
            float r = sqrt(random2);

            Vector3 w = normal;
            Vector3 u = (Vector3::CrossProduct((fabs(Vector3::Dot(w, position)) > 0.1f ? Vector3(0.0f, 1.0f, 0.0f) : Vector3(1.0f)), w)).Normalize();
            Vector3 v = Vector3::CrossProduct(w, u);

            Vector3 d = (u * cos(theta) * r + v * sin(theta) * r + w * std::sqrtf(1.0f - random2)).Normalize();
            return Ray(position, d);
        }

        static Ray WeirdThingThatMightWork2(const Vector3& x, const Vector3& nl, float random1, float random2)
        {
            float r1 = 2.0f * Pi<float> * random1;
            float r2 = random2;
            float r2s = std::sqrtf(r2);

            Vector3 w = nl;
            //Vector3 u = (Vector3::CrossProduct(std::fabs(w.X) > 0.1f ? Vector3(0.0f, 1.0f, 0.0f) : Vector3(1.0f)), w)).Normalize();
            Vector3 u = (Vector3::CrossProduct(std::fabs(w.X) > 0.1f ? Vector3(0.0f, 1.0f, 0.0f) : Vector3(1.0f), w)).Normalize();
            Vector3 v = Vector3::CrossProduct(w, u);
            Vector3 d = (u*std::cosf(r1) * r2s + v * std::sinf(r1) * r2s + w * std::sqrtf(1 - r2)).Normalize();

            return Ray(x + d * Epsilon, d);
        }
    };
}