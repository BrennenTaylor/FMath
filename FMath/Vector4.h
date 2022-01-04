/**
 * \file Vector4.h
 * @author Brennen Taylor (brtaylor1001@gmail.com)
 * @brief Declares the vector2 class
 * @version 0.1
 * @date 2019-03-12
 *
 * @copyright Copyright (c) 2019
 *
 */

#pragma once

#include <iostream>

/**
 * @brief The farlor 3d graphics libraries
*/
namespace Farlor
{
    /**
     * @brief Class which represents a 4D vector
     *
     */
    class Vector4
    {
    public:
        union
        {
            float m_data[4];
            struct
            {
                float x;
                float y;
                float z;
                float w;
            };
            struct
            {
                float r;
                float g;
                float b;
                float a;
            };
        };

    public:
        /**
         * @brief Construct a new Vector 4 object, defaults all values to 0
         *
         */
        explicit Vector4() noexcept;
        /**
         * @brief Construct a new Vector 4 object, sets all elements to value
         *
         * @param value
         */
        explicit Vector4(float value) noexcept;
        /**
         * @brief Construct a new Vector 4 object, set x, y, z, w to the specified values
         *
         * @param xNew
         * @param yNew
         * @param zNew
         * @param wNew
         */
        explicit Vector4(float xNew, float yNew, float zNew, float wNew) noexcept;

        /**
         * @brief Overloaded += operator, element wise
         *
         * @param rhs
         * @return Vector4&
         */
        Vector4& operator+=(const Vector4 &rhs) noexcept;
        /**
         * @brief Overloaded + operator, element wise
         *
         * @param vec
         * @return Vector4
         */
        Vector4 operator+(const Vector4 &vec) const noexcept;
        /**
         * @brief Overloaded -= operator, element wise
         *
         * @param rhs
         * @return Vector4&
         */
        Vector4& operator-=(const Vector4 &rhs) noexcept;
        /**
         * @brief Overloaded - operator, element wise
         *
         * @param vec
         * @return Vector4
         */
        Vector4 operator-(const Vector4 &vec) const noexcept;
        /**
         * @brief Overloaded *= operator, element wise
         *
         * @param rhs
         * @return Vector4&
         */
        Vector4& operator*=(const Vector4 &rhs) noexcept;
        /**
         * @brief Overloaded * operator, element wise
         *
         * @param vec
         * @return Vector4
         */
        Vector4 operator*(const Vector4 &vec) const noexcept;
        /**
         * @brief Overloaded /= operator, element wise
         *
         * @param rhs
         * @return Vector4&
         */
        Vector4& operator/=(const Vector4 &rhs) noexcept;
        /**
         * @brief Overloaded / operator, element wise
         *
         * @param vec
         * @return Vector4
         */
        Vector4 operator/(const Vector4 &vec) const noexcept;
        /**
         * @brief Overloaded %= operator for dot product
         *
         * @param rhs
         * @return Vector4&
         */
        Vector4& operator%=(const Vector4 &rhs) = delete;
        /**
         * @brief Overloaded % operator for dot product
         *
         * @param vec
         * @return float
         */
        float operator%(const Vector4 &vec) const = delete;
        /**
         * @brief Overload == operator, element wise
         *
         * @param other
         * @return true
         * @return false
         */
        bool operator==(const Vector4 &other) const noexcept;
        /**
         * @brief Overloade != operator, element wise
         *
         * @param other
         * @return true
         * @return false
         */
        bool operator!=(const Vector4 &other) const noexcept;

        /**
         * @brief Overload [] operator
         *
         * @param index
         * @return float&
         */
        float& operator[] (const int index) noexcept;
        /**
         * @brief Overload [] operator
         *
         * @param index
         * @return const float&
         */
        const float& operator[] (const int index) const;

        /**
         * @brief Overload *= operator for element wise multiplication with scalar
         *
         * @param rhs
         * @return Vector4&
         */
        Vector4& operator*=(const float &rhs) noexcept;
        /**
         * @brief Overload * operator for element wise multiplcation with scalar
         *
         * @param rhs
         * @return Vector4
         */
        Vector4 operator*(const float &rhs) const noexcept;
        /**
         * @brief Overload /= operator for element wise division with scalar
         *
         * @param rhs
         * @return Vector4&
         */
        Vector4& operator/=(const float &rhs) noexcept;
        /**
         * @brief Overload / operator for element wise division with scalar
         *
         * @param rhs
         * @return Vector4
         */
        Vector4 operator/(const float &rhs) const noexcept;

        /**
         * @brief overload * operator for scalar * vector order
         *
         * @param lhs
         * @param rhs
         * @return Vector4
         */
        friend Vector4 operator*(float lhs, const Vector4& rhs) noexcept;

        /**
         * @brief Overload stream operator for pretty printing a vector 4d.
         *
         * @param os
         * @param vec
         * @return std::ostream&
         */
        friend std::ostream& operator<<(std::ostream& os, const Vector4& vec);
        /**
         * @brief Calculate magnitude of a vector
         *
         * @return float
         */
        float Magnitude() const noexcept;
        /**
         * @brief Calculate square magnitude of a vector, allows for avoiding sqrt calculation
         *
         * @return float
         */
        float SqrMagnitude() const noexcept;
        /**
         * @brief Returns normalized version of the vector
         *
         * @return Vector4
         */
        Vector4 Normalized() const noexcept;
        /**
         * @brief Normalize the current vector
         *
         */
        void Normalize() noexcept;
        /**
         * @brief Calculate dot product with another vector
         *
         * @param other
         * @return float
         */
        float Dot(const Vector4& other) const noexcept;
    };
}

namespace std
{
    template<> struct hash<Farlor::Vector4>
    {
        size_t operator()(const Farlor::Vector4& vector) const noexcept
        {
            size_t const h1(std::hash<float>{}(vector.x));
            size_t const h2(std::hash<float>{}(vector.y));
            size_t const h3(std::hash<float>{}(vector.z));
            size_t const h4(std::hash<float>{}(vector.w));
            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
        }
    };
}
