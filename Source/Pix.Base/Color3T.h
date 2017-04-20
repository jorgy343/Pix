#pragma once

#include <math.h>
#include <algorithm>

namespace Pix::Base
{
    template <typename T> class Color4T;
    template <typename T> class Vector2T;
    template <typename T> class Vector3T;
    template <typename T> class Vector4T;

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

        explicit Color3T(const Color4T<T>& color4)
            : Color3T(color4.Red, color4.Green, color4.Blue)
        {

        }

        Color3T(const Vector2T<T>& vector2, T blue)
            : Color3T(vector2.X, vector2.Y, blue)
        {

        }

        explicit Color3T(const Vector3T<T>& vector3)
            : Color3T(vector3.X, vector3.Y, vector3.Z)
        {

        }

        explicit Color3T(const Vector4T<T>& vector4)
            : Color3T(vector4.X, vector4.Y, vector4.Z)
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
            Red = abs(Red);
            Green = abs(Green);
            Blue = abs(Blue);

            return *this;
        }

        Color3T& Clamp(const Color3T& min, const Color3T& max)
        {
            Red = std::min(std::max(Red, min.Red), max.Red);
            Green = std::min(std::max(Green, min.Green), max.Green);
            Blue = std::min(std::max(Blue, min.Blue), max.Blue);

            return *this;
        }

        T GetLength() const
        {
            return sqrt(GetLengthSquared());
        }

        T GetLengthSquared() const
        {
            return Red * Red + Green * Green + Blue * Blue;
        }

        Color3T& Negate()
        {
            Red = -Red;
            Green = -Green;
            Blue = -Blue;

            return *this;
        }

        // Static members.
        static Color3T Abs(const Color3T& color)
        {
            return Color3T(
                abs(color.Red),
                abs(color.Green),
                abs(color.Blue));
        }

        static Color3T Add(const Color3T& left, const Color3T& right)
        {
            return left + right;
        }

        static Color3T Clamp(const Color3T& color, const Color3T& min, const Color3T& max)
        {
            return Color3T(
                std::min(std::max(color.Red, min.Red), max.Red),
                std::min(std::max(color.Green, min.Green), max.Green),
                std::min(std::max(color.Blue, min.Blue), max.Blue));
        }

        static Color3T Divide(const Color3T& left, T right)
        {
            return left / right;
        }

        static Color3T Divide(T left, const Color3T& right)
        {
            return left / right;
        }

        static Color3T Lerp(const Color3T& start, const Color3T& end, T amount)
        {
            return start + (end - start) * amount;
        }

        static Color3T Max(const Color3T& color1, const Color3T& color2)
        {
            return Color3T(
                std::max(color1.Red, color2.Red),
                std::max(color1.Green, color2.Green),
                std::max(color1.Blue, color2.Blue));
        }

        static Color3T Min(const Color3T& color1, const Color3T& color2)
        {
            return Color3T(
                std::min(color1.Red, color2.Red),
                std::min(color1.Green, color2.Green),
                std::min(color1.Blue, color2.Blue));
        }

        static Color3T Modulate(const Color3T& left, const Color3T& right)
        {
            return Color3T(
                left.Red * right.Red,
                left.Green * right.Green,
                left.Blue * right.Blue);
        }

        static Color3T Multiply(const Color3T& left, T right)
        {
            return left * right;
        }

        static Color3T Multiply(T left, const Color3T& right)
        {
            return left * right;
        }

        static Color3T Negate(const Color3T& color)
        {
            return Color3T(
                -color.Red,
                -color.Green,
                -color.Blue);
        }

        static Color3T Posit(const Color3T& color)
        {
            return Color3T(
                +color.Red,
                +color.Green,
                +color.Blue);
        }

        static Color3T SmoothStep(const Color3T& start, const Color3T& end, T amount)
        {
            T calculatedAmount = (amount > (T)1) ? (T)1 : ((amount < (T)0) ? (T)0 : amount);
            calculatedAmount = (calculatedAmount * calculatedAmount) * ((T)3 - ((T)2 * calculatedAmount));

            return start + (end - start) * amount;
        }

        static Color3T Subtract(const Color3T& left, const Color3T& right)
        {
            return left - right;
        }

        // Operator members.
        bool operator==(const Color3T& value) const
        {
            return Red == value.Red && Green == value.Green && Blue == value.Blue;
        }

        bool operator!=(const Color3T& value) const
        {
            return Red != value.Red || Green != value.Green || Blue != value.Blue;
        }

        Color3T operator+() const
        {
            Color3T result;

            result.Red = +Red;
            result.Green = +Green;
            result.Blue = +Blue;

            return result;
        }

        Color3T operator-() const
        {
            Color3T result;

            result.Red = -Red;
            result.Green = -Green;
            result.Blue = -Blue;

            return result;
        }

        Color3T operator+(const Color3T& color) const
        {
            Color3T result;

            result.Red = Red + color.Red;
            result.Green = Green + color.Green;
            result.Blue = Blue + color.Blue;

            return result;
        }

        Color3T operator-(const Color3T& color) const
        {
            Color3T result;

            result.Red = Red - color.Red;
            result.Green = Green - color.Green;
            result.Blue = Blue - color.Blue;

            return result;
        }

        Color3T operator*(T scalar) const
        {
            Color3T result;

            result.Red = Red * scalar;
            result.Green = Green * scalar;
            result.Blue = Blue * scalar;

            return result;
        }

        Color3T operator*(const Color3T& color) const
        {
            Color3T result;

            result.Red = Red * color.Red;
            result.Green = Green * color.Green;
            result.Blue = Blue * color.Blue;

            return result;
        }

        Color3T operator/(T scalar) const
        {
            Color3T result;

            result.Red = Red / scalar;
            result.Green = Green / scalar;
            result.Blue = Blue / scalar;

            return result;
        }

        Color3T& operator+=(const Color3T& color)
        {
            Red += color.Red;
            Green += color.Green;
            Blue += color.Blue;

            return *this;
        }

        Color3T& operator-=(const Color3T& color)
        {
            Red -= color.Red;
            Green -= color.Green;
            Blue -= color.Blue;

            return *this;
        }

        Color3T& operator*=(T scalar)
        {
            Red *= scalar;
            Green *= scalar;
            Blue *= scalar;

            return *this;
        }

        Color3T& operator+=(T scalar)
        {
            Red += scalar;
            Green += scalar;
            Blue += scalar;

            return *this;
        }
    };

    template <typename T>
    Color3T<T> operator*(T left, const Color3T<T>& right)
    {
        return Color3T<T>(
            left * right.Red,
            left * right.Green,
            left * right.Blue);
    }

    template <typename T>
    Color3T<T> operator/(T left, const Color3T<T>& right)
    {
        return Color3T<T>(
            left / right.Red,
            left / right.Green,
            left / right.Blue);
    }
}