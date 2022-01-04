/**
 * \file Vector2.h
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
     * @brief Class representing a 2D vector
     *
     */
    class Vector2
    {
    public:
        union
        {
            float m_data[2];
            struct
            {
                float x;
                float y;
            };
        };

    public:
        /**
         * @brief Construct a new Vector 2 object with x and y defaulting to 0.0
         *
         */
        explicit Vector2() noexcept;
        /**
         * @brief Construct a new Vector 2 object from single value for x and y
         *
         * @param value X and Y are set to this
         */
        explicit Vector2(float value) noexcept;
        /**
         * @brief Construct a new Vector 2 object with specified x and y values
         *
         * @param xNew X value set to this
         * @param yNew Y value set to this
         */
        explicit Vector2(float xNew, float yNew) noexcept;

        /**
         * @brief overload += operator for Vector2
         *
         * @param rhs
         * @return Vector2&
         */
        Vector2& operator+=(const Vector2 &rhs) noexcept;
        /**
         * @brief overload + operator for Vector2
         *
         * @param vec
         * @return Vector2
         */
        Vector2 operator+(const Vector2 &vec) const noexcept;
        /**
         * @brief overload -= operator for Vector2
         *
         * @param rhs
         * @return Vector2&
         */
        Vector2& operator-=(const Vector2 &rhs) noexcept;
        /**
         * @brief overload - operator for Vector2
         *
         * @param vec
         * @return Vector2
         */
        Vector2 operator-(const Vector2 &vec) const noexcept;
        /**
         * @brief overload *= operator, element wise multiplaction
         *
         * @param rhs
         * @return Vector2&
         */
        Vector2& operator*=(const Vector2 &rhs) noexcept;
        /**
         * @brief overload * operator, element wise multiplaction
         *
         * @param vec
         * @return Vector2
         */
        Vector2 operator*(const Vector2 &vec) const noexcept;
        /**
         * @brief overload /= operator, element wise
         *
         * @param rhs
         * @return Vector2&
         */
        Vector2& operator/=(const Vector2 &rhs) noexcept;
        /**
         * @brief overload / operator, element wise
         *
         * @param vec
         * @return Vector2
         */
        Vector2 operator/(const Vector2 &vec) const noexcept;

        /**
         * @brief Makes no sense in this context
         *
         * @param rhs
         * @return Vector2&
         */
        Vector2& operator%=(const Vector2 &rhs) = delete;
        /**
         * @brief overload % operator, overloaded for dot product
         *
         * @param vec
         * @return float
         */
        float operator%(const Vector2 &vec) const = delete;
        /**
         * @brief overload == operator, element wise
         *
         * @param other
         * @return bool
         */
        bool operator==(const Vector2 &other) const noexcept;
        /**
         * @brief overload != operator, element wise
         *
         * @param other
         * @return bool
         */
        bool operator!=(const Vector2 &other) const noexcept;

        /**
         * @brief overload *= operator, element wise multiplcation with float scalar
         *
         * @param rhs
         * @return Vector2&
         */
        Vector2& operator*=(const float &rhs) noexcept;
        /**
         * @brief overload * operator, element wise multiplcation with float scalar
         *
         * @param rhs
         * @return Vector2
         */
        Vector2 operator*(const float &rhs) const noexcept;

        /**
         * @brief overload /= operator, element wise division by float scalar
         *
         * @param rhs
         * @return Vector2&
         */
        Vector2& operator/=(const float &rhs) noexcept;
        /**
         * @brief overload / operator, element wise division by float scalar
         *
         * @param rhs
         * @return Vector2
         */
        Vector2 operator/(const float &rhs) const noexcept;

        /**
         * @brief Standalone \* operator for float \* vector2 multiplication
         *
         * @param lhs
         * @param rhs
         * @return Vector2
         */
        friend Vector2 operator*(const float lhs, const Vector2& rhs) noexcept;

        /**
         * @brief Overload of streaming operator, convenience for writing out structure
         *
         * @param os
         * @param vec
         * @return std::ostream&
         */
        friend std::ostream& operator<<(std::ostream& os, const Vector2& vec);

        /**
         * @brief Calculate the magnitude of the vector
         *
         * @return float
         */
        float Magnitude() const noexcept;
        /**
         * @brief Simply calculate the sqr magnitude, avoids the sqrt call. Faster if you dont need the full magnitude.
         *
         * @return float
         */
        float SqrMagnitude() const noexcept;
        /**
         * @brief Returnes the normalized version of the current vector
         *
         * @return Vector2
         */
        Vector2 Normalized() const noexcept;
        /**
         * @brief Normalizes the current vector
         *
         */
        void Normalize() noexcept;

        /**
         * @brief Calculate dot product with another vector
         *
         * @param other
         * @return float
         */
        float Dot(const Vector2& other) const noexcept;
    };
}

namespace std
{
    template<> struct hash<Farlor::Vector2>
    {
        size_t operator()(Farlor::Vector2 const& vector) const noexcept
        {
            return ((hash<float>()(vector.x) ^ (hash<float>()(vector.y) << 1)) >> 1);
        }
    };
}
