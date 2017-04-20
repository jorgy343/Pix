#pragma once

#include <math.h>
#include <algorithm>

namespace Pix::Base
{
    template <typename T> class Color3T;
    template <typename T> class Color4T;
    template <typename T> class Vector2T;
    template <typename T> class Vector3T;

    template <typename T>
    class Vector4T
    {
    public:
        T X, Y, Z, W;

        Vector4T() = default;

        Vector4T(const Color3T<T>& color3, T alpha)
            : Vector4T(color3.Red, color3.Green, color3.Blue, alpha)
        {

        }

        explicit Vector4T(const Color4T<T>& color4)
            : Vector4T(color4.Red, color4.Green, color4.Blue, color4.Alpha)
        {

        }

        Vector4T(const Vector2T<T>& vector2, T z, T w)
            : Vector4T(vector2.X, vector2.Y, z, w)
        {

        }

        Vector4T(const Vector3T<T>& vector3, T w)
            : Vector4T(vector3.X, vector3.Y, vector3.Z, w)
        {

        }

        explicit Vector4T(T scalar)
            : Vector4T(scalar, scalar, scalar, scalar)
        {

        }

        Vector4T(T x, T y, T z, T w)
            : X(x), Y(y), Z(z), W(w)
        {

        }

        // Instance members.
        Vector4T& Abs()
        {
            *this = Abs(*this);
            return *this;
        }

        Vector4T& Clamp(const Vector4T& min, const Vector4T& max)
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

        Vector4T& Negate()
        {
            *this = Negate(*this);
            return *this;
        }

        Vector4T& Normalize()
        {
            *this = Normalize(*this);
            return *this;
        }

        // Static members.
        static Vector4T Abs(const Vector4T& vector)
        {
            return Vector4T(
                abs(vector.X),
                abs(vector.Y),
                abs(vector.Z),
                abs(vector.W));
        }

        static Vector4T Add(T left, const Vector4T& right)
        {
            return Vector4T(
                left + right.X,
                left + right.Y,
                left + right.Z,
                left + right.W);
        }

        static Vector4T Add(const Vector4T& left, T right)
        {
            return Vector4T(
                left.X + right,
                left.Y + right,
                left.Z + right,
                left.W + right);
        }

        static Vector4T Add(const Vector4T& left, const Vector4T& right)
        {
            return Vector4T(
                left.X + right.X,
                left.Y + right.Y,
                left.Z + right.Z,
                left.W + right.W);
        }

        static Vector4T Barycentric(const Vector4T& vector1, const Vector4T& vector2, const Vector4T& vector3, T amount1, T amount2)
        {
            return Vector4T(
                (vector1.X + (amount1 * (vector2.X - vector1.X))) + (amount2 * (vector3.X - vector1.X)),
                (vector1.Y + (amount1 * (vector2.Y - vector1.Y))) + (amount2 * (vector3.Y - vector1.Y)),
                (vector1.Z + (amount1 * (vector2.Z - vector1.Z))) + (amount2 * (vector3.Z - vector1.Z)),
                (vector1.W + (amount1 * (vector2.W - vector1.W))) + (amount2 * (vector3.W - vector1.W)));
        }

        static Vector4T CatmullRom(const Vector4T& vector1, const Vector4T& vector2, const Vector4T& vector3, const Vector4T& vector4, T amount)
        {
            T squared = amount * amount;
            T cubed = amount * squared;

            Vector4T result;

            result.X = (T)0.5 * (((((T)2 * vector2.X) + ((-vector1.X + vector3.X) * amount)) +
                ((((((T)2 * vector1.X) - ((T)5 * vector2.X)) + ((T)4 * vector3.X)) - vector4.X) * squared)) +
                ((((-vector1.X + ((T)3 * vector2.X)) - ((T)3 * vector3.X)) + vector4.X) * cubed));

            result.Y = (T)0.5 * (((((T)2 * vector2.Y) + ((-vector1.Y + vector3.Y) * amount)) +
                ((((((T)2 * vector1.Y) - ((T)5 * vector2.Y)) + ((T)4 * vector3.Y)) - vector4.Y) * squared)) +
                ((((-vector1.Y + ((T)3 * vector2.Y)) - ((T)3 * vector3.Y)) + vector4.Y) * cubed));

            result.Z = (T)0.5 * (((((T)2 * vector2.Z) + ((-vector1.Z + vector3.Z) * amount)) +
                ((((((T)2 * vector1.Z) - ((T)5 * vector2.Z)) + ((T)4 * vector3.Z)) - vector4.Z) * squared)) +
                ((((-vector1.Z + ((T)3 * vector2.Z)) - ((T)3 * vector3.Z)) + vector4.Z) * cubed));

            result.W = (T)0.5 * (((((T)2 * vector2.W) + ((-vector1.W + vector3.W) * amount)) +
                ((((((T)2 * vector1.W) - ((T)5 * vector2.W)) + ((T)4 * vector3.W)) - vector4.W) * squared)) +
                ((((-vector1.W + ((T)3 * vector2.W)) - ((T)3 * vector3.W)) + vector4.W) * cubed));

            return result;
        }

        static Vector4T Clamp(const Vector4T& vector, const Vector4T& min, const Vector4T& max)
        {
            return Vector4T(
                std::min(std::max(vector.X, min.X), max.X),
                std::min(std::max(vector.Y, min.Y), max.Y),
                std::min(std::max(vector.Z, min.Z), max.Z),
                std::min(std::max(vector.W, min.W), max.W));
        }

        static T Distance(const Vector4T& left, const Vector4T& right)
        {
            return sqrt(DistanceSquared(left, right));
        }

        static T DistanceSquared(const Vector4T& left, const Vector4T& right)
        {
            T x = left.X - right.X;
            T y = left.Y - right.Y;
            T z = left.Z - right.Z;
            T w = left.W - right.W;

            return x * x + y * y + z * z + w * w;
        }

        static Vector4T Divide(T left, const Vector4T& right)
        {
            return Vector4T(
                left / right.X,
                left / right.Y,
                left / right.Z,
                left / right.W);
        }

        static Vector4T Divide(const Vector4T& left, T right)
        {
            return Vector4T(
                left.X / right,
                left.Y / right,
                left.Z / right,
                left.W / right);
        }

        static T Dot(const Vector4T& left, const Vector4T& right)
        {
            return left.X * right.X + left.Y * right.Y + left.Z * right.Z + left.W * right.W;
        }

        static bool Equals(const Vector4T& left, const Vector4T& right)
        {
            return left.X == right.X && left.Y == right.Y && left.Z == right.Z && left.W == right.W;
        }

        static T GetLength(const Vector4T& vector)
        {
            return sqrt(GetLengthSquared(vector));
        }

        static T GetLengthSquared(const Vector4T& vector)
        {
            return vector.X * vector.X + vector.Y * vector.Y + vector.Z * vector.Z + vector.W * vector.W;
        }

        static Vector4T Hermite(const Vector4T& vector1, const Vector4T& tangent1, const Vector4T& vector2, const Vector4T& tangent2, T amount)
        {
            T squared = amount * amount;
            T cubed = amount * squared;
            T part1 = (2.0f * cubed - 3.0f * squared) + 1.0f;
            T part2 = -2.0f * cubed + 3.0f * squared;
            T part3 = (cubed - 2.0f * squared) + amount;
            T part4 = cubed - squared;

            return Vector4T(
                vector1.X * part1 + vector2.X * part2 + tangent1.X * part3 + tangent2.X * part4,
                vector1.Y * part1 + vector2.Y * part2 + tangent1.Y * part3 + tangent2.Y * part4,
                vector1.Z * part1 + vector2.Z * part2 + tangent1.Z * part3 + tangent2.Z * part4,
                vector1.W * part1 + vector2.W * part2 + tangent1.W * part3 + tangent2.W * part4);
        }

        static bool IsZeroVector(const Vector4T& vector)
        {
            return vector.X == (T)0 && vector.Y == (T)0 && vector.Z == (T)0 && vector.W == (T)0;
        }

        static Vector4T Lerp(const Vector4T& start, const Vector4T& end, T amount)
        {
            return start + (end - start) * amount;
        }

        static Vector4T Max(const Vector4T& vector1, const Vector4T& vector2)
        {
            return Vector4T(
                std::max(vector1.X, vector2.X),
                std::max(vector1.Y, vector2.Y),
                std::max(vector1.Z, vector2.Z),
                std::max(vector1.W, vector2.W));
        }

        static Vector4T Min(const Vector4T& vector1, const Vector4T& vector2)
        {
            return Vector4T(
                std::min(vector1.X, vector2.X),
                std::min(vector1.Y, vector2.Y),
                std::min(vector1.Z, vector2.Z),
                std::min(vector1.W, vector2.W));
        }

        static Vector4T Modulate(const Vector4T& left, const Vector4T& right)
        {
            return Vector4T(
                left.X * right.X,
                left.Y * right.Y,
                left.Z * right.Z,
                left.W * right.W);
        }

        static Vector4T Multiply(T left, const Vector4T& right)
        {
            return Vector4T(
                left * right.X,
                left * right.Y,
                left * right.Z,
                left * right.W);
        }

        static Vector4T Multiply(const Vector4T& left, T right)
        {
            return Vector4T(
                left.X * right,
                left.Y * right,
                left.Z * right,
                left.W * right);
        }

        static Vector4T Negate(const Vector4T& vector)
        {
            return Vector4T(
                -vector.X,
                -vector.Y,
                -vector.Z,
                -vector.W);
        }

        static Vector4T Normalize(const Vector4T& vector)
        {
            T inverseLength = (T)1 / GetLength(vector);
            return Vector4T(
                vector.X * inverseLength,
                vector.Y * inverseLength,
                vector.Z * inverseLength,
                vector.W * inverseLength);
        }

        static bool NotEquals(const Vector4T& left, const Vector4T& right)
        {
            return left.X != right.X || left.Y != right.Y || left.Z != right.Z || left.W != right.W;
        }

        static Vector4T Posit(const Vector4T& vector)
        {
            return Vector4T(
                +vector.X,
                +vector.Y,
                +vector.Z,
                +vector.W);
        }

        static Vector4T SmoothStep(const Vector4T& start, const Vector4T& end, T amount)
        {
            T calculatedAmount = (amount > (T)1) ? (T)1 : ((amount < (T)0) ? (T)0 : amount);
            calculatedAmount = (calculatedAmount * calculatedAmount) * ((T)3 - ((T)2 * calculatedAmount));

            return start + (end - start) * amount;
        }

        static Vector4T Subtract(T left, const Vector4T& right)
        {
            return Vector4T(
                left - right.X,
                left - right.Y,
                left - right.Z,
                left - right.W);
        }

        static Vector4T Subtract(const Vector4T& left, T right)
        {
            return Vector4T(
                left.X - right,
                left.Y - right,
                left.Z - right,
                left.W - right);
        }

        static Vector4T Subtract(const Vector4T& left, const Vector4T& right)
        {
            return Vector4T(
                left.X - right.X,
                left.Y - right.Y,
                left.Z - right.Z,
                left.W - right.W);
        }

        // Operator members.
        bool operator==(const Vector4T& right) const
        {
            return Equals(*this, right);
        }

        bool operator!=(const Vector4T& right) const
        {
            return NotEquals(*this, right);
        }

        Vector4T operator+() const
        {
            return Posit(*this);
        }

        Vector4T operator-() const
        {
            return Negate(*this);
        }

        Vector4T operator+(T right) const
        {
            return Add(*this, right);
        }

        Vector4T operator+(const Vector4T& right) const
        {
            return Add(*this, right);
        }

        Vector4T operator-(T right) const
        {
            return Subtract(*this, right);
        }

        Vector4T operator-(const Vector4T& right) const
        {
            return Subtract(*this, right);
        }

        Vector4T operator*(T right) const
        {
            return Multiply(*this, right);
        }

        Vector4T operator/(T right) const
        {
            return Divide(*this, right);
        }

        Vector4T& operator+=(T right)
        {
            *this = Add(*this, right);
            return *this;
        }

        Vector4T& operator+=(const Vector4T& right)
        {
            *this = Add(*this, right);
            return *this;
        }

        Vector4T& operator-=(T right)
        {
            *this = Subtract(*this, right);
            return *this;
        }

        Vector4T& operator-=(const Vector4T& right)
        {
            *this = Subtract(*this, right);
            return *this;
        }

        Vector4T& operator*=(T right)
        {
            *this = Multiply(*this, right);
            return *this;
        }

        Vector4T& operator/=(T right)
        {
            *this = Divide(*this, right);
            return *this;
        }
    };

    template <typename T>
    Vector4T<T> operator+(T left, const Vector4T<T>& right)
    {
        return right.Add(left, right);
    }

    template <typename T>
    Vector4T<T> operator-(T left, const Vector4T<T>& right)
    {
        return right.Subtract(left, right);
    }

    template <typename T>
    Vector4T<T> operator*(T left, const Vector4T<T>& right)
    {
        return right.Multiply(left, right);
    }

    template <typename T>
    Vector4T<T> operator/(T left, const Vector4T<T>& right)
    {
        return right.Divide(left, right);
    }
}