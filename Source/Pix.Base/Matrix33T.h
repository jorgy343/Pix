#pragma once

#include <math.h>
#include <algorithm>

namespace Pix::Base
{
    template <typename T> class Vector2T;
    template <typename T> class Vector3T;

    template <typename T>
    class Matrix33T
    {
    public:
        T
            M11, M12, M13,
            M21, M22, M23,
            M31, M32, M33;

        Matrix33T() = default;

        Matrix33T(const Vector3T<T>& row1, const Vector3T<T>& row2, const Vector3T<T>& row3)
            : Matrix33T(
                row1.X, row1.Y, row1.Z,
                row2.X, row2.Y, row2.Z,
                row3.X, row3.Y, row3.Z)
        {

        }

        explicit Matrix33T(T scalar)
            : Matrix33T(
                scalar, scalar, scalar,
                scalar, scalar, scalar,
                scalar, scalar, scalar)
        {

        }

        Matrix33T(
            T m11, T m12, T m13,
            T m21, T m22, T m23,
            T m31, T m32, T m33)
            :
            M11(m11), M12(m12), M13(m13),
            M21(m21), M22(m22), M23(m23),
            M31(m31), M32(m32), M33(m33)
        {

        }

        // Instance members.
        T GetDeterminant() const
        {
            return
                M11 * M22 * M33 +
                M12 * M23 * M13 +
                M13 * M21 * M32 -
                M13 * M22 * M32 -
                M12 * M21 * M33 -
                M11 * M23 * M32;
        }

        Matrix33T& Invert()
        {
            Invert(*this);
            return *this;
        }

        Matrix33T& Negate()
        {
            Negate(*this);
            return *this;
        }

        Matrix33T& Transpose()
        {
            Transpose(*this);
            return *this;
        }

        // Static members.
        static Matrix33T Add(const Matrix33T& left, const Matrix33T& right)
        {
            Matrix33T result;

            result.M11 = left.M11 + right.M11;
            result.M11 = left.M12 + right.M12;
            result.M11 = left.M13 + right.M13;

            result.M21 = left.M21 + right.M21;
            result.M21 = left.M22 + right.M22;
            result.M21 = left.M23 + right.M23;

            result.M31 = left.M31 + right.M31;
            result.M31 = left.M32 + right.M32;
            result.M31 = left.M33 + right.M33;

            return result;
        }

        static Matrix33T CreateScale(T scalar)
        {
            return CreateScale(scalar, scalar, scalar);
        }

        static Matrix33T CreateScale(const Vector3T<T>& vector)
        {
            return CreateScale(vector.X, vector.Y, vector.Z);
        }

        static Matrix33T CreateScale(T x, T y, T z)
        {
            return Matrix33T(
                x, 0, 0,
                0, y, 0,
                0, 0, z);
        }

        static Matrix33T CreateIdentity()
        {
            return Matrix33T(
                1, 0, 0,
                0, 1, 0,
                0, 0, 1);
        }

        static Matrix33T EntrywiseProduct(const Matrix33T& left, const Matrix33T& right)
        {
            Matrix33T result;

            result.M11 = left.M11 * right.M11;
            result.M12 = left.M12 * right.M12;
            result.M13 = left.M13 * right.M13;

            result.M21 = left.M21 * right.M21;
            result.M22 = left.M22 * right.M22;
            result.M23 = left.M23 * right.M23;

            result.M31 = left.M31 * right.M31;
            result.M32 = left.M32 * right.M32;
            result.M33 = left.M33 * right.M33;

            return result;
        }

        static bool Equals(const Matrix33T& left, const Matrix33T& right)
        {
            return
                left.M11 == right.M11 &&
                left.M12 == right.M12 &&
                left.M13 == right.M13 &&

                left.M21 == right.M21 &&
                left.M22 == right.M22 &&
                left.M23 == right.M23 &&

                left.M31 == right.M31 &&
                left.M32 == right.M32 &&
                left.M33 == right.M33;
        }

        static Matrix33T Invert(const Matrix33T& matrix)
        {

        }

        static Matrix33T Lerp(const Matrix33T& start, const Matrix33T& end, T amount)
        {
            Matrix33T result;

            result.M11 = start.M11 + (end.M11 - start.M11) * amount;
            result.M12 = start.M12 + (end.M12 - start.M12) * amount;
            result.M13 = start.M13 + (end.M13 - start.M13) * amount;

            result.M21 = start.M21 + (end.M21 - start.M21) * amount;
            result.M22 = start.M22 + (end.M22 - start.M22) * amount;
            result.M23 = start.M23 + (end.M23 - start.M23) * amount;

            result.M31 = start.M31 + (end.M31 - start.M31) * amount;
            result.M32 = start.M32 + (end.M32 - start.M32) * amount;
            result.M33 = start.M33 + (end.M33 - start.M33) * amount;

            return result;
        }

        static Matrix33T Multiply(T left, const Matrix33T& right)
        {
            Matrix33T result;

            result.M11 = left * right.M11;
            result.M12 = left * right.M12;
            result.M13 = left * right.M13;

            result.M21 = left * right.M21;
            result.M22 = left * right.M22;
            result.M23 = left * right.M23;

            result.M31 = left * right.M31;
            result.M32 = left * right.M32;
            result.M33 = left * right.M33;

            return result;
        }

        static Matrix33T Multiply(const Matrix33T& left, T right)
        {
            Matrix33T result;

            result.M11 = left.M11 * right;
            result.M12 = left.M12 * right;
            result.M13 = left.M13 * right;

            result.M21 = left.M21 * right;
            result.M22 = left.M22 * right;
            result.M23 = left.M23 * right;

            result.M31 = left.M31 * right;
            result.M32 = left.M32 * right;
            result.M33 = left.M33 * right;

            return result;
        }

        static Matrix33T Multiply(const Matrix33T& left, const Matrix33T& right)
        {
            Matrix33T result;

            result.M11 = left.M11 * right.M11 + left.M12 * right.M21 + left.M13 * right.M31;
            result.M12 = left.M11 * right.M12 + left.M12 * right.M22 + left.M13 * right.M32;
            result.M13 = left.M11 * right.M13 + left.M12 * right.M23 + left.M13 * right.M33;

            result.M21 = left.M21 * right.M11 + left.M22 * right.M21 + left.M23 * right.M31;
            result.M22 = left.M21 * right.M12 + left.M22 * right.M22 + left.M23 * right.M32;
            result.M23 = left.M21 * right.M13 + left.M22 * right.M23 + left.M23 * right.M33;

            result.M31 = left.M31 * right.M11 + left.M32 * right.M21 + left.M33 * right.M31;
            result.M32 = left.M31 * right.M12 + left.M32 * right.M22 + left.M33 * right.M32;
            result.M33 = left.M31 * right.M13 + left.M32 * right.M23 + left.M33 * right.M33;

            return result;
        }

        static Vector3T<T> Multiply(T x, T y, T z, const Matrix33T& matrix)
        {
            return Multiply(Vector3T<T>(x, y, z), matrix);
        }

        static Vector3T<T> Multiply(const Vector3T<T>& vector, const Matrix33T& matrix)
        {
            Vector3T<T> result;

            result.X = vector.X * matrix.M11 + vector.Y * matrix.M21 + vector.Z * matrix.M31;
            result.Y = vector.X * matrix.M12 + vector.Y * matrix.M22 + vector.Z * matrix.M32;
            result.Z = vector.X * matrix.M13 + vector.Y * matrix.M23 + vector.Z * matrix.M33;

            return result;
        }

        static Matrix33T Negate(const Matrix33T& matrix)
        {
            Matrix33T result;

            result.M11 = -matrix.M11;
            result.M12 = -matrix.M12;
            result.M13 = -matrix.M13;

            result.M21 = -matrix.M21;
            result.M22 = -matrix.M22;
            result.M23 = -matrix.M23;

            result.M31 = -matrix.M31;
            result.M32 = -matrix.M32;
            result.M33 = -matrix.M33;

            return result;
        }

        static bool NotEquals(const Matrix33T& left, const Matrix33T& right)
        {
            return
                left.M11 != right.M11 ||
                left.M12 != right.M12 ||
                left.M13 != right.M13 ||

                left.M21 != right.M21 ||
                left.M22 != right.M22 ||
                left.M23 != right.M23 ||

                left.M31 != right.M31 ||
                left.M32 != right.M32 ||
                left.M33 != right.M33;
        }

        static Matrix33T Posit(const Matrix33T& matrix)
        {
            Matrix33T result;

            result.M11 = +matrix.M11;
            result.M12 = +matrix.M12;
            result.M13 = +matrix.M13;

            result.M21 = +matrix.M21;
            result.M22 = +matrix.M22;
            result.M23 = +matrix.M23;

            result.M31 = +matrix.M31;
            result.M32 = +matrix.M32;
            result.M33 = +matrix.M33;

            return result;
        }

        static Matrix33T SmoothStep(const Matrix33T& start, const Matrix33T& end, T amount)
        {
            Matrix33T result;

            amount = (amount > 1) ? 1 : ((amount < 0) ? 0 : amount);
            amount = (amount * amount) * (3 - (2 * amount));

            result.M11 = start.M11 + (end.M11 - start.M11) * amount;
            result.M12 = start.M12 + (end.M12 - start.M12) * amount;
            result.M13 = start.M13 + (end.M13 - start.M13) * amount;

            result.M21 = start.M21 + (end.M21 - start.M21) * amount;
            result.M22 = start.M22 + (end.M22 - start.M22) * amount;
            result.M23 = start.M23 + (end.M23 - start.M23) * amount;

            result.M31 = start.M31 + (end.M31 - start.M31) * amount;
            result.M32 = start.M32 + (end.M32 - start.M32) * amount;
            result.M33 = start.M33 + (end.M33 - start.M33) * amount;

            return result;
        }

        static Matrix33T Subtract(const Matrix33T& left, const Matrix33T& right)
        {
            Matrix33T result;

            result.M11 = left.M11 - right.M11;
            result.M11 = left.M12 - right.M12;
            result.M11 = left.M13 - right.M13;

            result.M21 = left.M21 - right.M21;
            result.M21 = left.M22 - right.M22;
            result.M21 = left.M23 - right.M23;

            result.M31 = left.M31 - right.M31;
            result.M31 = left.M32 - right.M32;
            result.M31 = left.M33 - right.M33;

            return result;
        }

        static Matrix33T Transpose(const Matrix33T& matrix)
        {
            Matrix33T result;

            result.M11 = matrix.M11;
            result.M12 = matrix.M21;
            result.M13 = matrix.M31;

            result.M21 = matrix.M12;
            result.M22 = matrix.M22;
            result.M23 = matrix.M32;

            result.M31 = matrix.M13;
            result.M32 = matrix.M23;
            result.M33 = matrix.M33;

            return result;
        }

        // Operator members.
        bool operator==(const Matrix33T& right) const
        {
            return Equals(*this, right);
        }

        bool operator!=(const Matrix33T& right) const
        {
            return NotEquals(*this, right);
        }

        Matrix33T operator+() const
        {
            return Posit(*this);
        }

        Matrix33T operator-() const
        {
            return Negate(*this);
        }

        Matrix33T operator+(const Matrix33T& right) const
        {
            return Add(*this, right);
        }

        Matrix33T operator-(const Matrix33T& right) const
        {
            return Subtract(*this, right);
        }

        Matrix33T operator*(T right) const
        {
            return Multiply(*this, right);
        }

        Matrix33T operator*(const Matrix33T& right) const
        {
            return Multiply(*this, right);
        }

        Matrix33T& operator+=(const Matrix33T& right)
        {
            *this = Add(*this, right);
            return *this;
        }

        Matrix33T& operator-=(const Matrix33T& right)
        {
            *this = Subtract(*this, right);
            return *this;
        }

        Matrix33T& operator*=(T right)
        {
            *this = Multiply(*this, right);
            return *this;
        }
    };

    template <typename T>
    Matrix33T<T> operator*(T left, const Matrix33T<T>& right)
    {
        return right.Multiply(left, right);
    }

    template <typename T>
    Vector3T<T> operator*(const Vector3T<T>& left, const Matrix33T<T>& right)
    {
        return right.Multiply(left, right);
    }
}