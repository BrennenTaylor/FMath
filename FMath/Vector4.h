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
        explicit Vector4();
        /**
         * @brief Construct a new Vector 4 object, sets all elements to value
         *
         * @param value
         */
        explicit Vector4(float value);
        /**
         * @brief Construct a new Vector 4 object, set x, y, z, w to the specified values
         *
         * @param xNew
         * @param yNew
         * @param zNew
         * @param wNew
         */
        explicit Vector4(float xNew, float yNew, float zNew, float wNew);

        /**
         * @brief Overloaded += operator, element wise
         *
         * @param rhs
         * @return Vector4&
         */
        Vector4& Vector4::operator+=(const Vector4 &rhs);
        /**
         * @brief Overloaded + operator, element wise
         *
         * @param vec
         * @return Vector4
         */
        Vector4 operator+(const Vector4 &vec) const;
        /**
         * @brief Overloaded -= operator, element wise
         *
         * @param rhs
         * @return Vector4&
         */
        Vector4& Vector4::operator-=(const Vector4 &rhs);
        /**
         * @brief Overloaded - operator, element wise
         *
         * @param vec
         * @return Vector4
         */
        Vector4 operator-(const Vector4 &vec) const;
        /**
         * @brief Overloaded *= operator, element wise
         *
         * @param rhs
         * @return Vector4&
         */
        Vector4& Vector4::operator*=(const Vector4 &rhs);
        /**
         * @brief Overloaded * operator, element wise
         *
         * @param vec
         * @return Vector4
         */
        Vector4 operator*(const Vector4 &vec) const;
        /**
         * @brief Overloaded /= operator, element wise
         *
         * @param rhs
         * @return Vector4&
         */
        Vector4& Vector4::operator/=(const Vector4 &rhs);
        /**
         * @brief Overloaded / operator, element wise
         *
         * @param vec
         * @return Vector4
         */
        Vector4 operator/(const Vector4 &vec) const;
        /**
         * @brief Overloaded %= operator for dot product
         *
         * @param rhs
         * @return Vector4&
         */
        Vector4& Vector4::operator%=(const Vector4 &rhs) = delete;
        /**
         * @brief Overloaded % operator for dot product
         *
         * @param vec
         * @return float
         */
        float operator%(const Vector4 &vec) const;
        /**
         * @brief Overload == operator, element wise
         *
         * @param other
         * @return true
         * @return false
         */
        bool operator==(const Vector4 &other) const;
        /**
         * @brief Overloade != operator, element wise
         *
         * @param other
         * @return true
         * @return false
         */
        bool operator!=(const Vector4 &other) const;

        /**
         * @brief Overload [] operator
         *
         * @param index
         * @return float&
         */
        float& operator[] (const int index);
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
        Vector4& operator*=(const float &rhs);
        /**
         * @brief Overload * operator for element wise multiplcation with scalar
         *
         * @param rhs
         * @return Vector4
         */
        Vector4 operator*(const float &rhs) const;
        /**
         * @brief Overload /= operator for element wise division with scalar
         *
         * @param rhs
         * @return Vector4&
         */
        Vector4& operator/=(const float &rhs);
        /**
         * @brief Overload / operator for element wise division with scalar
         *
         * @param rhs
         * @return Vector4
         */
        Vector4 operator/(const float &rhs) const;

        /**
         * @brief overload * operator for scalar * vector order
         *
         * @param lhs
         * @param rhs
         * @return Vector4
         */
        friend Vector4 operator*(float lhs, const Vector4& rhs);

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
        float Magnitude() const;
        /**
         * @brief Calculate square magnitude of a vector, allows for avoiding sqrt calculation
         *
         * @return float
         */
        float SqrMagnitude() const;
        /**
         * @brief Returns normalized version of the vector
         *
         * @return Vector4
         */
        Vector4 Normalized() const;
        /**
         * @brief Normalize the current vector
         *
         */
        void Normalize();
        /**
         * @brief Calculate dot product with another vector
         *
         * @param other
         * @return float
         */
        float Dot(const Vector4& other) const;
    };
}