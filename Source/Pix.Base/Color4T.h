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
            Red = abs(Red);
            Green = abs(Green);
            Blue = abs(Blue);
            Alpha = abs(Alpha);

            return *this;
        }

        Color4T& Clamp(const Color4T& min, const Color4T& max)
        {
            Red = std::min(std::max(Red, min.Red), max.Red);
            Green = std::min(std::max(Green, min.Green), max.Green);
            Blue = std::min(std::max(Blue, min.Blue), max.Blue);
            Alpha = std::min(std::max(Alpha, min.Alpha), max.Alpha);

            return *this;
        }

        T GetLength() const
        {
            return sqrt(GetLengthSquared());
        }

        T GetLengthSquared() const
        {
            return Red * Red + Green * Green + Blue * Blue + Alpha * Alpha;
        }

        Color4T& Negate()
        {
            Red = -Red;
            Green = -Green;
            Blue = -Blue;
            Alpha = -Alpha;

            return *this;
        }

        // Static members.
        static Color4T Abs(const Color4T& color)
        {
            return Color4T(
                abs(color.Red),
                abs(color.Green),
                abs(color.Blue),
                abs(color.Alpha));
        }

        static Color4T Add(const Color4T& left, const Color4T& right)
        {
            return left + right;
        }

        static Color4T Clamp(const Color4T& color, const Color4T& min, const Color4T& max)
        {
            return Color4T(
                std::min(std::max(color.Red, min.Red), max.Red),
                std::min(std::max(color.Green, min.Green), max.Green),
                std::min(std::max(color.Blue, min.Blue), max.Blue),
                std::min(std::max(color.Alpha, min.Alpha), max.Alpha));
        }

        static Color4T Divide(const Color4T& left, T right)
        {
            return left / right;
        }

        static Color4T Divide(T left, const Color4T& right)
        {
            return left / right;
        }

        static Color4T Lerp(const Color4T& start, const Color4T& end, T amount)
        {
            return start + (end - start) * amount;
        }

        static Color4T Max(const Color4T& color1, const Color4T& color2)
        {
            return Color4T(
                std::max(color1.Red, color2.Red),
                std::max(color1.Green, color2.Green),
                std::max(color1.Blue, color2.Blue),
                std::max(color1.Alpha, color2.Alpha));
        }

        static Color4T Min(const Color4T& color1, const Color4T& color2)
        {
            return Color4T(
                std::min(color1.Red, color2.Red),
                std::min(color1.Green, color2.Green),
                std::min(color1.Blue, color2.Blue),
                std::min(color1.Alpha, color2.Alpha));
        }

        static Color4T Modulate(const Color4T& left, const Color4T& right)
        {
            return Color4T(
                left.Red * right.Red,
                left.Green * right.Green,
                left.Blue * right.Blue,
                left.Alpha * right.Alpha);
        }

        static Color4T Multiply(const Color4T& left, T right)
        {
            return left * right;
        }

        static Color4T Multiply(T left, const Color4T& right)
        {
            return left * right;
        }

        static Color4T Negate(const Color4T& color)
        {
            return Color4T(
                -color.Red,
                -color.Green,
                -color.Blue,
                -color.Alpha);
        }

        static Color4T Posit(const Color4T& color)
        {
            return Color4T(
                +color.Red,
                +color.Green,
                +color.Blue,
                +color.Alpha);
        }

        static Color4T SmoothStep(const Color4T& start, const Color4T& end, T amount)
        {
            T calculatedAmount = (amount > (T)1) ? (T)1 : ((amount < (T)0) ? (T)0 : amount);
            calculatedAmount = (calculatedAmount * calculatedAmount) * ((T)3 - ((T)2 * calculatedAmount));

            return start + (end - start) * amount;
        }

        static Color4T Subtract(const Color4T& left, const Color4T& right)
        {
            return left - right;
        }

        // Operator members.
        bool operator==(const Color4T& value) const
        {
            return Red == value.Red && Green == value.Green && Blue == value.Blue && Alpha == value.Alpha;
        }

        bool operator!=(const Color4T& value) const
        {
            return Red != value.Red || Green != value.Green || Blue != value.Blue || Alpha != value.Alpha;
        }

        Color4T operator+() const
        {
            Color4T result;

            result.Red = +Red;
            result.Green = +Green;
            result.Blue = +Blue;
            result.Alpha = +Alpha;

            return result;
        }

        Color4T operator-() const
        {
            Color4T result;

            result.Red = -Red;
            result.Green = -Green;
            result.Blue = -Blue;
            result.Alpha = -Alpha;

            return result;
        }

        Color4T operator+(const Color4T& color) const
        {
            Color4T result;

            result.Red = Red + color.Red;
            result.Green = Green + color.Green;
            result.Blue = Blue + color.Blue;
            result.Alpha = Alpha + color.Alpha;

            return result;
        }

        Color4T operator-(const Color4T& color) const
        {
            Color4T result;

            result.Red = Red - color.Red;
            result.Green = Green - color.Green;
            result.Blue = Blue - color.Blue;
            result.Alpha = Alpha - color.Alpha;

            return result;
        }

        Color4T operator*(T scalar) const
        {
            Color4T result;

            result.Red = Red * scalar;
            result.Green = Green * scalar;
            result.Blue = Blue * scalar;
            result.Alpha = Alpha * scalar;

            return result;
        }

        Color4T operator/(T scalar) const
        {
            Color4T result;

            result.Red = Red / scalar;
            result.Green = Green / scalar;
            result.Blue = Blue / scalar;
            result.Alpha = Alpha / scalar;

            return result;
        }

        Color4T& operator+=(const Color4T& color)
        {
            Red += color.Red;
            Green += color.Green;
            Blue += color.Blue;
            Alpha += color.Alpha;

            return *this;
        }

        Color4T& operator-=(const Color4T& color)
        {
            Red -= color.Red;
            Green -= color.Green;
            Blue -= color.Blue;
            Alpha -= color.Alpha;

            return *this;
        }

        Color4T& operator*=(T scalar)
        {
            Red *= scalar;
            Green *= scalar;
            Blue *= scalar;
            Alpha *= scalar;

            return *this;
        }

        Color4T& operator+=(T scalar)
        {
            Red += scalar;
            Green += scalar;
            Blue += scalar;
            Alpha += scalar;

            return *this;
        }
    };

    template <typename T>
    Color4T<T> operator*(T left, const Color4T<T>& right)
    {
        return Color4T<T>(
            left * right.Red,
            left * right.Green,
            left * right.Blue,
            left * right.Alpha);
    }

    template <typename T>
    Color4T<T> operator/(T left, const Color4T<T>& right)
    {
        return Color4T<T>(
            left / right.Red,
            left / right.Green,
            left / right.Blue,
            left / right.Alpha);
    }
}