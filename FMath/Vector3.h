/**
 * @file Vector3.h
 * @author Brennen Taylor (brtaylor1001@gmail.com)
 * @brief
 * @version 0.1
 * @date 2019-03-12
 *
 * @copyright Copyright (c) 2019
 *
 */
#pragma once

#include <iostream>

namespace Farlor
{
    /**
     * @brief Represents a 3D vector
     *
     */
    class Vector3
    {
    public:
        union
        {
            float m_data[3];
            struct
            {
                float x;
                float y;
                float z;
            };
        };

    public:
        /**
         * @brief Construct a new Vector 3 object, default x, y, z to 0
         *
         */
        explicit Vector3();
        /**
         * @brief Construct a new Vector 3 object, set x, y, z to value
         *
         * @param value
         */
        explicit Vector3(float value);
        /**
         * @brief Construct a new Vector 3 object, specify x, y, z values
         *
         * @param xNew
         * @param yNew
         * @param zNew
         */
        explicit Vector3(float xNew, float yNew, float zNew);

        /**
         * @brief overload += operator, element wise
         *
         * @param rhs
         * @return Vector3&
         */
        Vector3& operator+=(const Vector3 &rhs);
        /**
         * @brief Overload + operator, element wise
         *
         * @param vec
         * @return Vector3
         */
        Vector3 operator+(const Vector3 &vec) const;
        /**
         * @brief Overload -= operator, element wise
         *
         * @param rhs
         * @return Vector3&
         */
        Vector3& operator-=(const Vector3 &rhs);
        /**
         * @brief Overload - operator, element wise
         *
         * @param vec
         * @return Vector3
         */
        Vector3 operator-(const Vector3 &vec) const;
        /**
         * @brief Overload *= operator, element wise
         *
         * @param rhs
         * @return Vector3&
         */
        Vector3& operator*=(const Vector3 &rhs);
        /**
         * @brief Overload * operator, element wise
         *
         * @param vec
         * @return Vector3
         */
        Vector3 operator*(const Vector3 &vec) const;
        /**
         * @brief Overload /= operator, element wise
         *
         * @param rhs
         * @return Vector3&
         */
        Vector3& operator/=(const Vector3 &rhs);
        /**
         * @brief Overload / operator, element wise
         *
         * @param vec
         * @return Vector3
         */
        Vector3 operator/(const Vector3 &vec) const;
        /**
         * @brief Overload %= operator for dot product
         *
         * @param rhs
         * @return Vector3&
         */
        Vector3& operator%=(const Vector3 &rhs) = delete;
        /**
         * @brief Overload % operator for dot product
         *
         * @param vec
         * @return float
         */
        float operator%(const Vector3 &vec) const;
        /**
         * @brief Overload == operator, element wise
         *
         * @param other
         * @return bool
         */
        bool operator==(const Vector3 &other) const;
        /**
         * @brief Overload != operator, element wise
         *
         * @param other
         * @return bool
         */
        bool operator!=(const Vector3 &other) const;

        /**
         * @brief Overload index operator
         *
         * @param index
         * @return float&
         */
        float& operator[] (const int index);

        /**
         * @brief Overload *= operator with scalar, element wise
         *
         * @param rhs
         * @return Vector3&
         */
        Vector3& operator*=(const float &rhs);
        /**
         * @brief Overload * operator with scalar, element wise
         *
         * @param lhs
         * @param rhs
         * @return Vector3
         */
        friend Vector3 operator*(const Vector3 lhs, const float &rhs);

        /**
         * @brief Overload /= operator, scalar
         *
         * @param rhs
         * @return Vector3&
         */
        Vector3& operator/=( float &rhs);
        /**
         * @brief Overload / operator, scalar
         *
         * @param lhs
         * @param rhs
         * @return Vector3
         */
        friend Vector3 operator/(const Vector3 lhs, float &rhs);

        /**
         * @brief OVerload * operator, form float * vector3
         *
         * @param lhs
         * @param rhs
         * @return Vector3
         */
        friend Vector3 operator*(const float lhs, const Vector3& rhs);

        /**
         * @brief Overload streaming operator, convenience for outputing formatted vector
         *
         * @param os
         * @param vec
         * @return std::ostream&
         */
        friend std::ostream& operator<<(std::ostream& os, const Vector3& vec);

        /**
         * @brief Add a scalar to the vector, element wise
         *
         * @param other
         * @param scaler
         */
        void AddScaledVector(const Vector3& other, const float scaler);

        /**
         * @brief Calculate magnitude of vector
         *
         * @return float
         */
        float Magnitude() const;
        /**
         * @brief Calculate sqr magnitude of vector, can be used to avoid sqrt in specific cases
         *
         * @return float
         */
        float SqrMagnitude() const;
        /**
         * @brief Return normalized version of her vector
         *
         * @return Vector3
         */
        Vector3 Normalized() const;
        /**
         * @brief Normalize the current vector
         *
         */
        void Normalize();

        /**
         * @brief Calculate dot product between two vectors
         *
         * @param other
         * @return float
         */
        float Dot(const Vector3& other) const;
        /**
         * @brief Calculate the cross product between two vectors
         *
         * @param other
         * @return Vector3
         */
        Vector3 Cross(const Vector3& other) const;

        /**
         * @brief Take 3 vectors and orthoganolize them
         *
         * @param v0
         * @param v1
         * @param v2
         */
        static void MakeOrthonormalBasisRHS(Vector3& v0, Vector3& v1, Vector3& v2);
    };

    using Point = Vector3;
}

namespace std
{
    template<> struct hash<Farlor::Vector3>
    {
        size_t operator()(Farlor::Vector3 const& vector) const
        {
            return ((hash<float>()(vector.x) ^ (hash<float>()(vector.y) << 1)) >> 1) ^ (hash<float>()(vector.z) << 1);
        }
    };
}