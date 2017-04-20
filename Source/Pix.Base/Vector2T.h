#pragma once

#include <math.h>
#include <algorithm>

namespace Pix::Base
{
    template <typename T> class Color3T;
    template <typename T> class Color4T;
    template <typename T> class Vector3T;
    template <typename T> class Vector4T;

    template <typename T>
    class Vector2T
    {
    public:
        T X, Y;

        Vector2T() = default;

        explicit Vector2T(const Color3T<T>& color3)
            : Vector2T(color3.Red, color3.Green)
        {

        }

        explicit Vector2T(const Color4T<T>& color4)
            : Vector2T(color4.Red, color4.Green)
        {

        }

        explicit Vector2T(const Vector3T<T>& vector3)
            : Vector2T(vector3.X, vector3.Y)
        {

        }

        explicit Vector2T(const Vector4T<T>& vector4)
            : Vector2T(vector4.X, vector4.Y)
        {

        }

        explicit Vector2T(T scalar)
            : Vector2T(scalar, scalar)
        {

        }

        Vector2T(T x, T y)
            : X(x), Y(y)
        {

        }

        // Instance members.
        Vector2T& Abs()
        {
            *this = Abs(*this);
            return *this;
        }

        Vector2T& Clamp(const Vector2T& min, const Vector2T& max)
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

        Vector2T& Negate()
        {
            *this = Negate(*this);
            return *this;
        }

        Vector2T& Normalize()
        {
            *this = Normalize(*this);
            return *this;
        }

        // Static members.
        static Vector2T Abs(const Vector2T& vector)
        {
            return Vector2T(
                abs(vector.X),
                abs(vector.Y));
        }

        static Vector2T Add(T left, const Vector2T& right)
        {
            return Vector2T(
                left + right.X,
                left + right.Y);
        }

        static Vector2T Add(const Vector2T& left, T right)
        {
            return Vector2T(
                left.X + right,
                left.Y + right);
        }

        static Vector2T Add(const Vector2T& left, const Vector2T& right)
        {
            return Vector2T(
                left.X + right.X,
                left.Y + right.Y);
        }

        static Vector2T Barycentric(const Vector2T& vector1, const Vector2T& vector2, const Vector2T& vector3, T amount1, T amount2)
        {
            return Vector2T(
                (vector1.X + (amount1 * (vector2.X - vector1.X))) + (amount2 * (vector3.X - vector1.X)),
                (vector1.Y + (amount1 * (vector2.Y - vector1.Y))) + (amount2 * (vector3.Y - vector1.Y)));
        }

        static Vector2T CatmullRom(const Vector2T& vector1, const Vector2T& vector2, const Vector2T& vector3, const Vector2T& vector4, T amount)
        {
            T squared = amount * amount;
            T cubed = amount * squared;

            Vector2T result;

            result.X = (T)0.5 * (((((T)2 * vector2.X) + ((-vector1.X + vector3.X) * amount)) +
                ((((((T)2 * vector1.X) - ((T)5 * vector2.X)) + ((T)4 * vector3.X)) - vector4.X) * squared)) +
                ((((-vector1.X + ((T)3 * vector2.X)) - ((T)3 * vector3.X)) + vector4.X) * cubed));

            result.Y = (T)0.5 * (((((T)2 * vector2.Y) + ((-vector1.Y + vector3.Y) * amount)) +
                ((((((T)2 * vector1.Y) - ((T)5 * vector2.Y)) + ((T)4 * vector3.Y)) - vector4.Y) * squared)) +
                ((((-vector1.Y + ((T)3 * vector2.Y)) - ((T)3 * vector3.Y)) + vector4.Y) * cubed));

            return result;
        }

        static Vector2T Clamp(const Vector2T& vector, const Vector2T& min, const Vector2T& max)
        {
            return Vector2T(
                std::min(std::max(vector.X, min.X), max.X),
                std::min(std::max(vector.Y, min.Y), max.Y));
        }

        static T Distance(const Vector2T& left, const Vector2T& right)
        {
            return sqrt(DistanceSquared(left, right));
        }

        static T DistanceSquared(const Vector2T& left, const Vector2T& right)
        {
            T x = left.X - right.X;
            T y = left.Y - right.Y;

            return x * x + y * y;
        }

        static Vector2T Divide(T left, const Vector2T& right)
        {
            return left / right;
        }

        static Vector2T Divide(const Vector2T& left, T right)
        {
            return Vector2T(
                left / right.X,
                left / right.Y);
        }

        static T Dot(const Vector2T& left, const Vector2T& right)
        {
            return left.X * right.X + left.Y * right.Y;
        }

        static bool Equals(const Vector2T& left, const Vector2T& right)
        {
            return left.X == right.X && left.Y == right.Y;
        }

        static T GetLength(const Vector2T& vector)
        {
            return sqrt(GetLengthSquared(vector));
        }

        static T GetLengthSquared(const Vector2T& vector)
        {
            return vector.X * vector.X + vector.Y * vector.Y;
        }

        static Vector2T Hermite(const Vector2T& vector1, const Vector2T& tangent1, const Vector2T& vector2, const Vector2T& tangent2, T amount)
        {
            T squared = amount * amount;
            T cubed = amount * squared;
            T part1 = (2.0f * cubed - 3.0f * squared) + 1.0f;
            T part2 = -2.0f * cubed + 3.0f * squared;
            T part3 = (cubed - 2.0f * squared) + amount;
            T part4 = cubed - squared;

            return Vector2T(
                vector1.X * part1 + vector2.X * part2 + tangent1.X * part3 + tangent2.X * part4,
                vector1.Y * part1 + vector2.Y * part2 + tangent1.Y * part3 + tangent2.Y * part4);
        }

        static bool IsZeroVector(const Vector2T& vector)
        {
            return vector.X == (T)0 && vector.Y == (T)0;
        }

        static Vector2T Lerp(const Vector2T& start, const Vector2T& end, T amount)
        {
            return start + (end - start) * amount;
        }

        static Vector2T Max(const Vector2T& vector1, const Vector2T& vector2)
        {
            return Vector2T(
                std::max(vector1.X, vector2.X),
                std::max(vector1.Y, vector2.Y));
        }

        static Vector2T Min(const Vector2T& vector1, const Vector2T& vector2)
        {
            return Vector2T(
                std::min(vector1.X, vector2.X),
                std::min(vector1.Y, vector2.Y));
        }

        static Vector2T Modulate(const Vector2T& left, const Vector2T& right)
        {
            return Vector2T(
                left.X * right.X,
                left.Y * right.Y);
        }

        static Vector2T Multiply(T left, const Vector2T& right)
        {
            return Vector2T(
                left * right.X,
                left * right.Y);
        }

        static Vector2T Multiply(const Vector2T& left, T right)
        {
            return Vector2T(
                left.X * right,
                left.Y * right);
        }

        static Vector2T Negate(const Vector2T& vector)
        {
            return Vector2T(
                -vector.X,
                -vector.Y);
        }

        static Vector2T Normalize(const Vector2T& vector)
        {
            T inverseLength = (T)1 / GetLength(vector);
            return Vector2T(
                vector.X * inverseLength,
                vector.Y * inverseLength);
        }

        static bool NotEquals(const Vector2T& left, const Vector2T& right)
        {
            return left.X != right.X || left.Y != right.Y;
        }

        static Vector2T Posit(const Vector2T& vector)
        {
            return Vector2T(
                +vector.X,
                +vector.Y);
        }

        static Vector2T SmoothStep(const Vector2T& start, const Vector2T& end, T amount)
        {
            T calculatedAmount = (amount > (T)1) ? (T)1 : ((amount < (T)0) ? (T)0 : amount);
            calculatedAmount = (calculatedAmount * calculatedAmount) * ((T)3 - ((T)2 * calculatedAmount));

            return start + (end - start) * amount;
        }

        static Vector2T Subtract(T left, const Vector2T& right)
        {
            return Vector2T(
                left - right.X,
                left - right.Y);
        }

        static Vector2T Subtract(const Vector2T& left, T right)
        {
            return Vector2T(
                left.X - right,
                left.Y - right);
        }

        static Vector2T Subtract(const Vector2T& left, const Vector2T& right)
        {
            return Vector2T(
                left.X - right.X,
                left.Y - right.Y);
        }

        // Operator members.
        bool operator==(const Vector2T& right) const
        {
            return Equals(*this, right);
        }

        bool operator!=(const Vector2T& right) const
        {
            return NotEquals(*this, right);
        }

        Vector2T operator+() const
        {
            return Posit(*this);
        }

        Vector2T operator-() const
        {
            return Negate(*this);
        }

        Vector2T operator+(T right) const
        {
            return Add(*this, right);
        }

        Vector2T operator+(const Vector2T& right) const
        {
            return Add(*this, right);
        }

        Vector2T operator-(T right) const
        {
            return Subtract(*this, right);
        }

        Vector2T operator-(const Vector2T& right) const
        {
            return Subtract(*this, right);
        }

        Vector2T operator*(T right) const
        {
            return Multiply(*this, right);
        }

        Vector2T operator/(T right) const
        {
            return Divide(*this, right);
        }

        Vector2T& operator+=(T right)
        {
            *this = Add(*this, right);
            return *this;
        }

        Vector2T& operator+=(const Vector2T& right)
        {
            *this = Add(*this, right);
            return *this;
        }

        Vector2T& operator-=(T right)
        {
            *this = Subtract(*this, right);
            return *this;
        }

        Vector2T& operator-=(const Vector2T& right)
        {
            *this = Subtract(*this, right);
            return *this;
        }

        Vector2T& operator*=(T right)
        {
            *this = Multiply(*this, right);
            return *this;
        }

        Vector2T& operator/=(T right)
        {
            *this = Divide(*this, right);
            return *this;
        }
    };

    template <typename T>
    Vector2T<T> operator+(T left, const Vector2T<T>& right)
    {
        return right.Add(left, right);
    }

    template <typename T>
    Vector2T<T> operator-(T left, const Vector2T<T>& right)
    {
        return right.Subtract(left, right);
    }

    template <typename T>
    Vector2T<T> operator*(T left, const Vector2T<T>& right)
    {
        return right.Multiply(left, right);
    }

    template <typename T>
    Vector2T<T> operator/(T left, const Vector2T<T>& right)
    {
        return right.Divide(left, right);
    }
}