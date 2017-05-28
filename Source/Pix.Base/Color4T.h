#pragma once

#include <math.h>
#include <algorithm>

namespace Pix::Base
{
    template <typename T> class Color3T;
    template <typename T> class Vector2T;
    template <typename T> class Vector3T;
    template <typename T> class Vector4T;

    template <typename T>
    class Color4T
    {
    public:
        union
        {
            T R;
            T Red;
        };

        union
        {
            T G;
            T Green;
        };

        union
        {
            T B;
            T Blue;
        };

        union
        {
            T A;
            T Alpha;
        };

        Color4T() = default;

        Color4T(const Color3T<T>& color3, T alpha)
            : Color4T(color3.Red, color3.Green, color3.Blue, alpha)
        {

        }

        Color4T(const Vector2T<T>& vector2, T blue, T alpha)
            : Color4T(vector2.X, vector2.Y, blue, alpha)
        {

        }

        Color4T(const Vector3T<T>& vector3, T alpha)
            : Color4T(vector3.X, vector3.Y, vector3.Z, alpha)
        {

        }

        explicit Color4T(const Vector4T<T>& vector4)
            : Color4T(vector4.X, vector4.Y, vector4.Z, vector4.W)
        {

        }

        explicit Color4T(T scalar)
            : Color4T(scalar, scalar, scalar, scalar)
        {

        }

        Color4T(T red, T green, T blue, T alpha)
            : Red(red), Green(green), Blue(blue), Alpha(alpha)
        {

        }

        // Instance members.
        Color4T& Abs()
        {
            R = abs(R);
            G = abs(G);
            B = abs(B);
            A = abs(A);

            return *this;
        }

        Color4T& Clamp(const Color4T& min, const Color4T& max)
        {
            R = std::min(std::max(R, min.R), max.R);
            G = std::min(std::max(G, min.G), max.G);
            B = std::min(std::max(B, min.B), max.B);
            A = std::min(std::max(A, min.A), max.A);

            return *this;
        }

        T GetLength() const
        {
            return sqrt(R * R + G * G + B * B + A * A);
        }

        T GetLengthSquared() const
        {
            return R * R + G * G + B * B + A * A;
        }

        Color4T& Negate()
        {
            R = -R;
            G = -G;
            B = -B;
            A = -A;

            return *this;
        }

        // Static members.
        static Color4T Abs(const Color4T& color)
        {
            return Color4T(
                abs(color.R),
                abs(color.G),
                abs(color.B),
                abs(color.A));
        }

        static Color4T Add(const Color4T& left, const Color4T& right)
        {
            return Color4T(
                left.R + right.R,
                left.G + right.G,
                left.B + right.B,
                left.A + right.A);
        }

        static Color4T Clamp(const Color4T& color, const Color4T& min, const Color4T& max)
        {
            return Color4T(
                std::min(std::max(color.R, min.R), max.R),
                std::min(std::max(color.G, min.G), max.G),
                std::min(std::max(color.B, min.B), max.B),
                std::min(std::max(color.A, min.A), max.A));
        }

        static Color4T Divide(const Color4T& left, T right)
        {
            return Color4T(
                left.R / right,
                left.G / right,
                left.B / right,
                left.A / right);
        }

        static Color4T Divide(const Color4T& left, const Color4T& right)
        {
            return Color4T(
                left.R / right.R,
                left.G / right.G,
                left.B / right.B,
                left.A / right.A);
        }

        static bool Equals(const Color4T& left, const Color4T& right)
        {
            return R == value.R && G == value.G && B == value.B && A == value.A;
        }

        static Color4T Lerp(const Color4T& start, const Color4T& end, T amount)
        {
            return Color4T(
                start.R + (end.R - start.R) * amount,
                start.G + (end.G - start.G) * amount,
                start.B + (end.B - start.B) * amount,
                start.A + (end.A - start.A) * amount);
        }

        static Color4T Max(const Color4T& color1, const Color4T& color2)
        {
            return Color4T(
                std::max(color1.R, color2.R),
                std::max(color1.G, color2.G),
                std::max(color1.B, color2.B),
                std::max(color1.A, color2.A));
        }

        static Color4T Min(const Color4T& color1, const Color4T& color2)
        {
            return Color4T(
                std::min(color1.R, color2.R),
                std::min(color1.G, color2.G),
                std::min(color1.B, color2.B),
                std::min(color1.A, color2.A));
        }

        static Color4T Multiply(const Color4T& left, T right)
        {
            return Color4T(
                left.R * right,
                left.G * right,
                left.B * right,
                left.A * right);
        }

        static Color4T Multiply(T left, const Color4T& right)
        {
            return Color4T(
                left * right.R,
                left * right.G,
                left * right.B,
                left * right.A);
        }

        static Color4T Multiply(const Color4T& left, const Color4T& right)
        {
            return Color4T(
                left.R * right.R,
                left.G * right.G,
                left.B * right.B,
                left.A * right.A);
        }

        static Color4T Negate(const Color4T& color)
        {
            return Color4T(
                -color.R,
                -color.G,
                -color.B,
                -color.A);
        }

        static bool NotEquals(const Color4T& left, const Color4T& right)
        {
            return R != value.R || G != value.G || B != value.B || A != value.A;
        }

        static Color4T Posit(const Color4T& color)
        {
            return Color4T(
                +color.R,
                +color.G,
                +color.B,
                +color.A);
        }

        static Color4T SmoothStep(const Color4T& start, const Color4T& end, T amount)
        {
            T calculatedAmount = (amount > 1) ? 1 : ((amount < 0) ? 0 : amount);
            calculatedAmount = (calculatedAmount * calculatedAmount) * (3 - (2 * calculatedAmount));

            return Color4T(
                start.R + (end.R - start.R) * amount,
                start.G + (end.G - start.G) * amount,
                start.B + (end.B - start.B) * amount,
                start.A + (end.A - start.A) * amount);
        }

        static Color4T Subtract(const Color4T& left, const Color4T& right)
        {
            return Color4T(
                left.R - right.R,
                left.G - right.G,
                left.B - right.B,
                left.A - right.A);
        }

        // Operator members.
        bool operator==(const Color4T& value) const
        {
            return Equals(*this, value);
        }

        bool operator!=(const Color4T& value) const
        {
            return NotEquals(*this, value);
        }

        Color4T operator+() const
        {
            return Posit(*this);
        }

        Color4T operator-() const
        {
            return Negate(*this);
        }

        Color4T operator+(T right) const
        {
            return Add(*this, right);
        }

        Color4T operator+(const Color4T& right) const
        {
            return Add(*this, right);
        }

        Color4T operator-(T right) const
        {
            return Subtract(*this, right);
        }

        Color4T operator-(const Color4T& right) const
        {
            return Subtract(*this, right);
        }

        Color4T operator*(T right) const
        {
            return Multiply(*this, right);
        }

        Color4T operator*(const Color4T& right) const
        {
            return Multiply(*this, right);
        }

        Color4T operator/(T right) const
        {
            return Divide(*this, right);
        }

        Color4T operator/(const Color4T& right) const
        {
            return Divide(*this, right);
        }

        Color4T& operator+=(T right)
        {
            *this = Add(*this, right);
            return *this;
        }

        Color4T& operator+=(const Color4T& right)
        {
            *this = Add(*this, right);
            return *this;
        }

        Color4T& operator-=(T right)
        {
            *this = Subtract(*this, right);
            return *this;
        }

        Color4T& operator-=(const Color4T& right)
        {
            *this = Subtract(*this, right);
            return *this;
        }

        Color4T& operator*=(T right)
        {
            *this = Multiply(*this, right);
            return *this;
        }

        Color4T& operator*=(const Color4T& right)
        {
            *this = Multiply(*this, right);
            return *this;
        }

        Color4T& operator/=(T right)
        {
            *this = Divide(*this, right);
            return *this;
        }

        Color4T& operator/=(const Color4T& right)
        {
            *this = Divide(*this, right);
            return *this;
        }
    };

    template <typename T>
    Color4T<T> operator*(T left, const Color4T<T>& right)
    {
        return right.Multiply(left, right);
    }
}