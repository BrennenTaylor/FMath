/**
 * @file Matrix2x2.h
 * @author Brennen Taylor (brtaylor1001@gmail.com)
 * @brief
 * @version 0.1
 * @date 2019-03-12
 *
 * @copyright Copyright (c) 2019
 *
 */

#pragma once

#include "Vector2.h"

#include <iostream>

/**
 * @brief The farlor 3d graphics libraries
*/
namespace Farlor
{
    /**
     * @brief Class which represents a 2x2 matrix
     *
     */
    class Matrix2x2
    {
    public:
        union
        {
            float m_data[4];
            Vector2 m_rows[2];
            struct
            {
                float m_r1c1;
                float m_r1c2;
                float m_r2c1;
                float m_r2c2;
            };
        };

    public:
        /**
         * @brief Construct a new Matrix 2x2 object, defaults to identity matrix
         *
         */
        explicit Matrix2x2();
        /**
         * @brief Construct a new Matrix 2x2 object, defaults to specified values
         *
         * @param row0
         * @param row1
         */
        explicit Matrix2x2(Vector2 row0, Vector2 row1);


        /**
         * @brief Overloads += operator to add element wise
         *
         * @param rhs
         * @return Matrix2x2&
         */
        Matrix2x2& operator+=(const Matrix2x2 &rhs);
        /**
         * @brief Overloads + operator to add element wise
         *
         * @param vec
         * @return Matrix2x2
         */
        Matrix2x2 operator+( const Matrix2x2 &vec) const;
        /**
         * @brief Overload -= operator to subtract element wise
         *
         * @param rhs
         * @return Matrix2x2&
         */
        Matrix2x2& operator-=(const Matrix2x2 &rhs);
        /**
         * @brief Overload - operator to subtract element wise
         *
         * @param vec
         * @return Matrix2x2
         */
        Matrix2x2 operator-( const Matrix2x2 &vec) const;
        /**
         * @brief Overload *= to perform 2x2 matrix multiplcation
         *
         * @param rhs
         * @return Matrix2x2&
         */
        Matrix2x2& operator*=(const Matrix2x2 &rhs);
        /**
         * @brief Overload * operator to perform matrix multiplcation
         *
         * @param vec
         * @return Matrix2x2
         */
        Matrix2x2 operator*(const Matrix2x2 &vec) const;

        /**
         * @brief Overloads == to perform element wise
         *
         * @param other
         * @return true
         * @return false
         */
        bool operator==(const Matrix2x2 &other) const;
        /**
         * @brief Overloads != to perform element wise
         *
         * @param other
         * @return true
         * @return false
         */
        bool operator!=(const Matrix2x2 &other) const;

        /**
         * @brief Overload *= operator to multiply element wise by scalar
         *
         * @param rhs
         * @return Matrix2x2&
         */
        Matrix2x2& operator*=( float &rhs);
        /**
         * @brief Overload * operator to multiply element wise by scalar
         *
         * @param rhs
         * @return Matrix2x2
         */
        Matrix2x2 operator*(float &rhs) const;

        /**
         * @brief Overload * operator to multiply be vector2
         *
         * @param rhs
         * @return Vector2
         */
        Vector2 operator*(const Vector2 &rhs) const;

        /**
         * @brief Overload /= operator to divide element wise by scalar
         *
         * @param rhs
         * @return Matrix2x2&
         */
        Matrix2x2& operator/=( float &rhs);
        /**
         * @brief Overload / operator to divide element wise by scalar
         *
         * @param rhs
         * @return Matrix2x2
         */
        Matrix2x2 operator/( float &rhs) const;

        /**
         * @brief Overload * operator to allow float * Matrix2x2 multiplication
         *
         * @param lhs
         * @param rhs
         * @return Matrix2x2
         */
        friend Matrix2x2 operator*(float lhs, const Matrix2x2& rhs);

        /**
         * @brief Overload streaming operator for pretty printing a matrix2x2
         *
         * @param os
         * @param vec
         * @return std::ostream&
         */
        friend std::ostream& operator<<(std::ostream& os, Matrix2x2& vec);

        /**
         * @brief Return a transposed version of the matrix
         *
         * @return Matrix2x2
         */
        Matrix2x2 Transposed() const;
        /**
         * @brief Return an inversed version of the matrix
         *
         * @return Matrix2x2
         */
        Matrix2x2 Inversed() const;

    public:
        /**
         * @brief Always stores the identity 2d matrix
         *
         */
        static const Matrix2x2 s_Identity;
    };
}
