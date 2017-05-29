#pragma once

#include <math.h>
#include <algorithm>

namespace Pix::Base
{
    template <typename T> class Color3T;
    template <typename T> class Vector2T;
    template <typename T> class Vector3T;

    template <typename T>
    class Color3T
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

        Color3T() = default;

        Color3T(const Color3T<T>& color3)
            : Color3T(color3.Red, color3.Green, color3.Blue)
        {

        }

        Color3T(const Vector2T<T>& vector2, T blue)
            : Color3T(vector2.X, vector2.Y, blue)
        {

        }

        explicit Color3T(T scalar)
            : Color3T(scalar, scalar, scalar)
        {

        }

        Color3T(T red, T green, T blue)
            : Red(red), Green(green), Blue(blue)
        {

        }

        // Instance members.
        Color3T& Abs()
        {
            R = abs(R);
            G = abs(G);
            B = abs(B);

            return *this;
        }

        Color3T& Clamp(const Color3T& min, const Color3T& max)
        {
            R = std::min<T>(std::max<T>(R, min.R), max.R);
            G = std::min<T>(std::max<T>(G, min.G), max.G);
            B = std::min<T>(std::max<T>(B, min.B), max.B);

            return *this;
        }

        T GetLength() const
        {
            return sqrt(R * R + G * G + B * B);
        }

        T GetLengthSquared() const
        {
            return R * R + G * G + B * B;
        }

        Color3T& Negate()
        {
            R = -R;
            G = -G;
            B = -B;

            return *this;
        }

        // Static members.
        static Color3T Abs(const Color3T& color)
        {
            return Color3T(
                abs(color.R),
                abs(color.G),
                abs(color.B));
        }

        static Color3T Add(const Color3T& left, const Color3T& right)
        {
            return Color3T(
                left.R + right.R,
                left.G + right.G,
                left.B + right.B);
        }

        static Color3T Clamp(const Color3T& color, const Color3T& min, const Color3T& max)
        {
            return Color3T(
                std::min(std::max(color.R, min.R), max.R),
                std::min(std::max(color.G, min.G), max.G),
                std::min(std::max(color.B, min.B), max.B));
        }

        static Color3T Divide(const Color3T& left, T right)
        {
            return Color3T(
                left.R / right,
                left.G / right,
                left.B / right);
        }

        static Color3T Divide(const Color3T& left, const Color3T& right)
        {
            return Color3T(
                left.R / right.R,
                left.G / right.G,
                left.B / right.B);
        }

        static bool Equals(const Color3T& left, const Color3T& right)
        {
            return R == value.R && G == value.G && B == value.B;
        }

        static Color3T Lerp(const Color3T& start, const Color3T& end, T amount)
        {
            return Color3T(
                start.R + (end.R - start.R) * amount,
                start.G + (end.G - start.G) * amount,
                start.B + (end.B - start.B) * amount);
        }

        static Color3T Max(const Color3T& color1, const Color3T& color2)
        {
            return Color3T(
                std::max(color1.R, color2.R),
                std::max(color1.G, color2.G),
                std::max(color1.B, color2.B));
        }

        static Color3T Min(const Color3T& color1, const Color3T& color2)
        {
            return Color3T(
                std::min(color1.R, color2.R),
                std::min(color1.G, color2.G),
                std::min(color1.B, color2.B));
        }

        static Color3T Multiply(const Color3T& left, T right)
        {
            return Color3T(
                left.R * right,
                left.G * right,
                left.B * right);
        }

        static Color3T Multiply(T left, const Color3T& right)
        {
            return Color3T(
                left * right.R,
                left * right.G,
                left * right.B);
        }

        static Color3T Multiply(const Color3T& left, const Color3T& right)
        {
            return Color3T(
                left.R * right.R,
                left.G * right.G,
                left.B * right.B);
        }

        static Color3T Negate(const Color3T& color)
        {
            return Color3T(
                -color.R,
                -color.G,
                -color.B);
        }

        static bool NotEquals(const Color3T& left, const Color3T& right)
        {
            return R != value.R || G != value.G || B != value.B;
        }

        static Color3T Posit(const Color3T& color)
        {
            return Color3T(
                +color.R,
                +color.G,
                +color.B);
        }

        static Color3T SmoothStep(const Color3T& start, const Color3T& end, T amount)
        {
            T calculatedAmount = (amount > 1) ? 1 : ((amount < 0) ? 0 : amount);
            calculatedAmount = (calculatedAmount * calculatedAmount) * (3 - (2 * calculatedAmount));

            return Color3T(
                start.R + (end.R - start.R) * amount,
                start.G + (end.G - start.G) * amount,
                start.B + (end.B - start.B) * amount);
        }

        static Color3T Subtract(const Color3T& left, const Color3T& right)
        {
            return Color3T(
                left.R - right.R,
                left.G - right.G,
                left.B - right.B);
        }

        // Operator members.
        bool operator==(const Color3T& value) const
        {
            return Equals(*this, value);
        }

        bool operator!=(const Color3T& value) const
        {
            return NotEquals(*this, value);
        }

        Color3T operator+() const
        {
            return Posit(*this);
        }

        Color3T operator-() const
        {
            return Negate(*this);
        }

        Color3T operator+(T right) const
        {
            return Add(*this, right);
        }

        Color3T operator+(const Color3T& right) const
        {
            return Add(*this, right);
        }

        Color3T operator-(T right) const
        {
            return Subtract(*this, right);
        }

        Color3T operator-(const Color3T& right) const
        {
            return Subtract(*this, right);
        }

        Color3T operator*(T right) const
        {
            return Multiply(*this, right);
        }

        Color3T operator*(const Color3T& right) const
        {
            return Multiply(*this, right);
        }

        Color3T operator/(T right) const
        {
            return Divide(*this, right);
        }

        Color3T operator/(const Color3T& right) const
        {
            return Divide(*this, right);
        }

        Color3T& operator+=(T right)
        {
            *this = Add(*this, right);
            return *this;
        }

        Color3T& operator+=(const Color3T& right)
        {
            *this = Add(*this, right);
            return *this;
        }

        Color3T& operator-=(T right)
        {
            *this = Subtract(*this, right);
            return *this;
        }

        Color3T& operator-=(const Color3T& right)
        {
            *this = Subtract(*this, right);
            return *this;
        }

        Color3T& operator*=(T right)
        {
            *this = Multiply(*this, right);
            return *this;
        }

        Color3T& operator*=(const Color3T& right)
        {
            *this = Multiply(*this, right);
            return *this;
        }

        Color3T& operator/=(T right)
        {
            *this = Divide(*this, right);
            return *this;
        }

        Color3T& operator/=(const Color3T& right)
        {
            *this = Divide(*this, right);
            return *this;
        }
    };

    template <typename T>
    Color3T<T> operator*(T left, const Color3T<T>& right)
    {
        return right.Multiply(left, right);
    }
}