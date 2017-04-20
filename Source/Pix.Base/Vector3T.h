#pragma once

#include <math.h>
#include <algorithm>

namespace Pix::Base
{
    template <typename T> class Color3T;
    template <typename T> class Color4T;
    template <typename T> class Vector2T;
    template <typename T> class Vector4T;

    template <typename T>
    class Vector3T
    {
    public:
        T X, Y, Z;

        Vector3T() = default;

        explicit Vector3T(const Color3T<T>& color3)
            : Vector3T(color3.Red, color3.Green, color3.Blue)
        {

        }

        explicit Vector3T(const Color4T<T>& color4)
            : Vector3T(color4.Red, color4.Green, color4.Blue)
        {

        }

        Vector3T(const Vector2T<T>& vector2, T z)
            : Vector3T(vector2.X, vector2.Y, z)
        {

        }

        explicit Vector3T(const Vector4T<T>& vector4)
            : Vector3T(vector4.X, vector4.Y, vector4.Z)
        {

        }

        explicit Vector3T(T scalar)
            : Vector3T(scalar, scalar, scalar)
        {

        }

        Vector3T(T x, T y, T z)
            : X(x), Y(y), Z(z)
        {

        }

        // Instance members.
        Vector3T& Abs()
        {
            *this = Abs(*this);
            return *this;
        }

        Vector3T& Clamp(const Vector3T& min, const Vector3T& max)
        {
            *this = Clamp(*this, min, max);
            return *this;
        }

        T GetLength() const
        {
            return GetLength(*this);
        }

        T GetLengthSquared() const
        {
            return GetLengthSquared(*this);
        }

        bool IsZeroVector() const
        {
            return IsZeroVector(*this);
        }

        Vector3T& Negate()
        {
            *this = Negate(*this);
            return *this;
        }

        Vector3T& Normalize()
        {
            *this = Normalize(*this);
            return *this;
        }

        // Static members.
        static Vector3T Abs(const Vector3T& vector)
        {
            return Vector3T(
                abs(vector.X),
                abs(vector.Y),
                abs(vector.Z));
        }

        static Vector3T Add(T left, const Vector3T& right)
        {
            return Vector3T(
                left + right.X,
                left + right.Y,
                left + right.Z);
        }

        static Vector3T Add(const Vector3T& left, T right)
        {
            return Vector3T(
                left.X + right,
                left.Y + right,
                left.Z + right);
        }

        static Vector3T Add(const Vector3T& left, const Vector3T& right)
        {
            return Vector3T(
                left.X + right.X,
                left.Y + right.Y,
                left.Z + right.Z);
        }

        static Vector3T Barycentric(const Vector3T& vector1, const Vector3T& vector2, const Vector3T& vector3, T amount1, T amount2)
        {
            return Vector3T(
                (vector1.X + (amount1 * (vector2.X - vector1.X))) + (amount2 * (vector3.X - vector1.X)),
                (vector1.Y + (amount1 * (vector2.Y - vector1.Y))) + (amount2 * (vector3.Y - vector1.Y)),
                (vector1.Z + (amount1 * (vector2.Z - vector1.Z))) + (amount2 * (vector3.Z - vector1.Z)));
        }

        static Vector3T CatmullRom(const Vector3T& vector1, const Vector3T& vector2, const Vector3T& vector3, const Vector3T& vector4, T amount)
        {
            T squared = amount * amount;
            T cubed = amount * squared;

            Vector3T result;

            result.X = (T)0.5 * (((((T)2 * vector2.X) + ((-vector1.X + vector3.X) * amount)) +
                ((((((T)2 * vector1.X) - ((T)5 * vector2.X)) + ((T)4 * vector3.X)) - vector4.X) * squared)) +
                ((((-vector1.X + ((T)3 * vector2.X)) - ((T)3 * vector3.X)) + vector4.X) * cubed));

            result.Y = (T)0.5 * (((((T)2 * vector2.Y) + ((-vector1.Y + vector3.Y) * amount)) +
                ((((((T)2 * vector1.Y) - ((T)5 * vector2.Y)) + ((T)4 * vector3.Y)) - vector4.Y) * squared)) +
                ((((-vector1.Y + ((T)3 * vector2.Y)) - ((T)3 * vector3.Y)) + vector4.Y) * cubed));

            result.Z = (T)0.5 * (((((T)2 * vector2.Z) + ((-vector1.Z + vector3.Z) * amount)) +
                ((((((T)2 * vector1.Z) - ((T)5 * vector2.Z)) + ((T)4 * vector3.Z)) - vector4.Z) * squared)) +
                ((((-vector1.Z + ((T)3 * vector2.Z)) - ((T)3 * vector3.Z)) + vector4.Z) * cubed));

            return result;
        }

        static Vector3T Clamp(const Vector3T& vector, const Vector3T& min, const Vector3T& max)
        {
            return Vector3T(
                std::min(std::max(vector.X, min.X), max.X),
                std::min(std::max(vector.Y, min.Y), max.Y),
                std::min(std::max(vector.Z, min.Z), max.Z));
        }

        static Vector3T CrossProduct(const Vector3T& left, const Vector3T& right)
        {
            return Vector3T(
                left.Y * right.Z - left.Z * right.Y,
                left.Z * right.X - left.X * right.Z,
                left.X * right.Y - left.Y * right.X);
        }

        static T Distance(const Vector3T& left, const Vector3T& right)
        {
            return sqrt(DistanceSquared(left, right));
        }

        static T DistanceSquared(const Vector3T& left, const Vector3T& right)
        {
            T x = left.X - right.X;
            T y = left.Y - right.Y;
            T z = left.Z - right.Z;

            return x * x + y * y + z * z;
        }

        static Vector3T Divide(T left, const Vector3T& right)
        {
            return Vector3T(
                left / right.X,
                left / right.Y,
                left / right.Z);
        }

        static Vector3T Divide(const Vector3T& left, T right)
        {
            return Vector3T(
                left.X / right,
                left.Y / right,
                left.Z / right);
        }

        static T Dot(const Vector3T& left, const Vector3T& right)
        {
            return left.X * right.X + left.Y * right.Y + left.Z * right.Z;
        }

        static bool Equals(const Vector3T& left, const Vector3T& right)
        {
            return left.X == right.X && left.Y == right.Y && left.Z == right.Z;
        }

        static void Fresnel(const Vector3T& direction, const Vector3T& normal, T fromIndex, T toIndex, Vector3T* reflection, Vector3T* refraction, T* reflectionCoefficient, T* refractionCoefficient)
        {
            Vector3T b = Dot(direction, normal);
            Vector3T c = -b;

            T n = fromIndex / toIndex;
            T sinT2 = n * n * ((T)1 - c * c);

            // Reflection
            *reflection = direction - (T)2 * b * normal;

            // Refraction
            T refractionRadicand = (T)1 - sinT2;
            if (refractionRadicand < (T)0)
                *refraction = Vector3T((T)0);

            *refraction = (n * direction) + (n * c - sqrt(refractionRadicand)) * normal;

            // Reflection Coefficient
            T r0 = (fromIndex - toIndex) / (fromIndex + toIndex);
            r0 *= r0;

            T cosX = c;
            if (fromIndex > ToIndex)
                cosX = sqrt((T)1 - cosX);

            T x = (T)1 - cosX;
            *reflectionCoefficient = r0 + ((T)1 - r0) * x * x * x * x * x;
            *refractionCoefficient = (T)1 - *reflectionCoefficient;
        }

        static T GetLength(const Vector3T& vector)
        {
            return sqrt(GetLengthSquared(vector));
        }

        static T GetLengthSquared(const Vector3T& vector)
        {
            return vector.X * vector.X + vector.Y * vector.Y + vector.Z * vector.Z;
        }

        static Vector3T Hermite(const Vector3T& vector1, const Vector3T& tangent1, const Vector3T& vector2, const Vector3T& tangent2, T amount)
        {
            T squared = amount * amount;
            T cubed = amount * squared;
            T part1 = (2.0f * cubed - 3.0f * squared) + 1.0f;
            T part2 = -2.0f * cubed + 3.0f * squared;
            T part3 = (cubed - 2.0f * squared) + amount;
            T part4 = cubed - squared;

            return Vector3T(
                vector1.X * part1 + vector2.X * part2 + tangent1.X * part3 + tangent2.X * part4,
                vector1.Y * part1 + vector2.Y * part2 + tangent1.Y * part3 + tangent2.Y * part4,
                vector1.Z * part1 + vector2.Z * part2 + tangent1.Z * part3 + tangent2.Z * part4);
        }

        static bool IsZeroVector(const Vector3T& vector)
        {
            return vector.X == (T)0 && vector.Y == (T)0 && vector.Z == (T)0;
        }

        static Vector3T Lerp(const Vector3T& start, const Vector3T& end, T amount)
        {
            return start + (end - start) * amount;
        }

        static Vector3T Max(const Vector3T& vector1, const Vector3T& vector2)
        {
            return Vector3T(
                std::max(vector1.X, vector2.X),
                std::max(vector1.Y, vector2.Y),
                std::max(vector1.Z, vector2.Z));
        }

        static Vector3T Min(const Vector3T& vector1, const Vector3T& vector2)
        {
            return Vector3T(
                std::min(vector1.X, vector2.X),
                std::min(vector1.Y, vector2.Y),
                std::min(vector1.Z, vector2.Z));
        }

        static Vector3T Modulate(const Vector3T& left, const Vector3T& right)
        {
            return Vector3T(
                left.X * right.X,
                left.Y * right.Y,
                left.Z * right.Z);
        }

        static Vector3T Multiply(T left, const Vector3T& right)
        {
            return Vector3T(
                left * right.X,
                left * right.Y,
                left * right.Z);
        }

        static Vector3T Multiply(const Vector3T& left, T right)
        {
            return Vector3T(
                left.X * right,
                left.Y * right,
                left.Z * right);
        }

        static Vector3T Negate(const Vector3T& vector)
        {
            return Vector3T(
                -vector.X,
                -vector.Y,
                -vector.Z);
        }

        static Vector3T Normalize(const Vector3T& vector)
        {
            T inverseLength = (T)1 / GetLength(vector);
            return Vector3T(
                vector.X * inverseLength,
                vector.Y * inverseLength,
                vector.Z * inverseLength);
        }

        static bool NotEquals(const Vector3T& left, const Vector3T& right)
        {
            return left.X != right.X || left.Y != right.Y || left.Z != right.Z;
        }

        static Vector3T Posit(const Vector3T& vector)
        {
            return Vector3T(
                +vector.X,
                +vector.Y,
                +vector.Z);
        }

        static Vector3T Project(const Vector3T& vector1, const Vector3T& vector2)
        {
            return vector2 * (Dot(vector1, vector2) / Dot(vector2, vector2));
        }

        static Vector3T Reflect(const Vector3T& vector, const Vector3T& normal)
        {
            float twoDot = Dot(vector, normal) * 2.0f;
            return vector - normal * twoDot;
        }

        static Vector3T Refract(const Vector3T& direction, const Vector3T& normal, T fromIndex, T toIndex)
        {
            T n = fromIndex / toIndex;
            T c = -Dot(direction, normal);

            T underSquareRoot = (T)1 - n * n * ((T)1 - c * c);
            if (underSquareRoot < (T)0)
                return Vector3T((T)0);

            return (n * direction) + (n * c - sqrt(underSquareRoot)) * normal;
        }

        // Approximates the reflection coefficient.
        static T SchlickApproximation(const Vector3T& direction, const Vector3T& normal, T fromIndex, T toIndex)
        {
            T r₀ = (fromIndex / toIndex) / (fromIndex + toIndex);
            r₀ *= r₀;

            T cosθ = -Dot(direction, normal);
            T cosX = cosθ;

            if (fromIndex > toIndex)
            {
                T n = fromIndex / toIndex;
                T sinT = n * n * ((T)1 - cosθ * cosθ);

                if (sinT > (T)1)
                    return (T)1;

                cosX = sqrt((T)1 - sinT);
            }

            T x = (T)1 - cosX;
            return r₀ + ((T)1 - r₀) * x * x * x * x * x;
        }

        static Vector3T SmoothStep(const Vector3T& start, const Vector3T& end, T amount)
        {
            T calculatedAmount = (amount > (T)1) ? (T)1 : ((amount < (T)0) ? (T)0 : amount);
            calculatedAmount = (calculatedAmount * calculatedAmount) * ((T)3 - ((T)2 * calculatedAmount));

            return start + (end - start) * amount;
        }

        static Vector3T Subtract(T left, const Vector3T& right)
        {
            return Vector3T(
                left - right.X,
                left - right.Y,
                left - right.Z);
        }

        static Vector3T Subtract(const Vector3T& left, T right)
        {
            return Vector3T(
                left.X - right,
                left.Y - right,
                left.Z - right);
        }

        static Vector3T Subtract(const Vector3T& left, const Vector3T& right)
        {
            return Vector3T(
                left.X - right.X,
                left.Y - right.Y,
                left.Z - right.Z);
        }

        // Operator members.
        bool operator==(const Vector3T& right) const
        {
            return Equals(*this, right);
        }

        bool operator!=(const Vector3T& right) const
        {
            return NotEquals(*this, right);
        }

        Vector3T operator+() const
        {
            return Posit(*this);
        }

        Vector3T operator-() const
        {
            return Negate(*this);
        }

        Vector3T operator+(T right) const
        {
            return Add(*this, right);
        }

        Vector3T operator+(const Vector3T& right) const
        {
            return Add(*this, right);
        }

        Vector3T operator-(T right) const
        {
            return Subtract(*this, right);
        }

        Vector3T operator-(const Vector3T& right) const
        {
            return Subtract(*this, right);
        }

        Vector3T operator*(T right) const
        {
            return Multiply(*this, right);
        }

        Vector3T operator/(T right) const
        {
            return Divide(*this, right);
        }

        Vector3T& operator+=(T right)
        {
            *this = Add(*this, right);
            return *this;
        }

        Vector3T& operator+=(const Vector3T& right)
        {
            *this = Add(*this, right);
            return *this;
        }

        Vector3T& operator-=(T right)
        {
            *this = Subtract(*this, right);
            return *this;
        }

        Vector3T& operator-=(const Vector3T& right)
        {
            *this = Subtract(*this, right);
            return *this;
        }

        Vector3T& operator*=(T right)
        {
            *this = Multiply(*this, right);
            return *this;
        }

        Vector3T& operator/=(T right)
        {
            *this = Divide(*this, right);
            return *this;
        }
    };

    template <typename T>
    Vector3T<T> operator+(T left, const Vector3T<T>& right)
    {
        return right.Add(left, right);
    }

    template <typename T>
    Vector3T<T> operator-(T left, const Vector3T<T>& right)
    {
        return right.Subtract(left, right);
    }

    template <typename T>
    Vector3T<T> operator*(T left, const Vector3T<T>& right)
    {
        return right.Multiply(left, right);
    }

    template <typename T>
    Vector3T<T> operator/(T left, const Vector3T<T>& right)
    {
        return right.Divide(left, right);
    }
}