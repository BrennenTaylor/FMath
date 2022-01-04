/**
 * @file Matrix3x3.h
 * @author Brennen Taylor (brtaylor1001@gmail.com)
 * @brief
 * @version 0.1
 * @date 2019-03-12
 *
 * @copyright Copyright (c) 2019
 *
 */

#pragma once

#include "Vector3.h"

#include "Quaternion.h"

#include <array>
#include <iostream>

/**
 * @brief The farlor 3d graphics libraries
*/
namespace Farlor
{
    /**
     * @brief Class which represents a 3x3 matrix
     *
     */
    class Matrix3x3
    {
    public:
        union
        {
            std::array<float, 9> m_data;
            Vector3 m_rows[3];
            struct {
                float m_r0c0;
                float m_r0c1;
                float m_r0c2;
                float m_r1c0;
                float m_r1c1;
                float m_r1c2;
                float m_r2c0;
                float m_r2c1;
                float m_r2c2;
            };
        };

        explicit Matrix3x3() noexcept;
        explicit Matrix3x3(Vector3 row1, Vector3 row2, Vector3 row3) noexcept;
        explicit Matrix3x3(Quaternion q) noexcept;


        // Matrix3x3 & Matrix3x3
        // Add
        Matrix3x3& operator+=(const Matrix3x3 &rhs) noexcept;
        Matrix3x3 operator+( const Matrix3x3 &vec) const noexcept;
        // Subtract
        Matrix3x3& operator-=(const Matrix3x3 &rhs) noexcept;
         Matrix3x3 operator-( const Matrix3x3 &vec) const noexcept;
        // Multiply
        Matrix3x3& operator*=(const Matrix3x3 &rhs) noexcept;
        Matrix3x3 operator*(const Matrix3x3 &vec) const noexcept;

        // Equality
        bool operator==(const Matrix3x3 &other) const noexcept;
        bool operator!=(const Matrix3x3 &other) const noexcept;

        // Vector & T
        // Multiply
        Matrix3x3& operator*=( float &rhs) noexcept;
        Matrix3x3 operator*(float &rhs) const noexcept;

        Vector3 operator*(const Vector3 &rhs) const noexcept;

        // Divide
        Matrix3x3& operator/=( float &rhs) noexcept;
        Matrix3x3 operator/( float &rhs) const noexcept;

        // Standalone
        friend Matrix3x3 operator*(float lhs, const Matrix3x3& rhs) noexcept;

        // Out Streaming
        friend std::ostream& operator<<(std::ostream& os, Matrix3x3& vec);

        Matrix3x3 Transposed() const noexcept;
        Matrix3x3 Inversed() const;

        static Quaternion ConvertToQuaternion(Matrix3x3& mat);

        static Matrix3x3 s_Identity;
    };
}
