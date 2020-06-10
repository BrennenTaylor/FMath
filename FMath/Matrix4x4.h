/**
 * @file Matrix4x4.h
 * @author Brennen Taylor (brtaylor1001@gmail.com)
 * @brief
 * @version 0.1
 * @date 2019-03-12
 *
 * @copyright Copyright (c) 2019
 *
 */

#pragma once

#include "Vector4.h"
#include "Vector3.h"
#include "Quaternion.h"

#include <iostream>

/**
 * @brief The farlor 3d graphics libraries
*/
namespace Farlor
{
    /**
     * @brief Class which represents a 4x4 matrix
     *
     */
    class Matrix4x4
    {
    public:
        union
        {
            float m_data[16];
            Vector4 m_rows[4];
            struct
            {
                float m_r1c1;
                float m_r1c2;
                float m_r1c3;
                float m_r1c4;
                float m_r2c1;
                float m_r2c2;
                float m_r2c3;
                float m_r2c4;
                float m_r3c1;
                float m_r3c2;
                float m_r3c3;
                float m_r3c4;
                float m_r4c1;
                float m_r4c2;
                float m_r4c3;
                float m_r4c4;
            };
        };

    public:
        Matrix4x4();
        Matrix4x4(const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4);
        Matrix4x4(const Quaternion& q, const Vector3& pos);
        Matrix4x4(float r1c1, float r1c2, float r1c3, float r1c4,
            float r2c1, float r2c2, float r2c3, float r2c4,
            float r3c1, float r3c2, float r3c3, float r3c4,
            float r4c1, float r4c2, float r4c3, float r4c4);

        Matrix4x4& Matrix4x4::operator+=(const Matrix4x4 &rhs);
        Matrix4x4 operator+(const Matrix4x4 &vec) const;
        Matrix4x4& Matrix4x4::operator-=(const Matrix4x4 &rhs);
        Matrix4x4 operator-(const Matrix4x4 &vec) const;
        Matrix4x4& Matrix4x4::operator*=(const Matrix4x4 &rhs);
        Matrix4x4 operator*(const Matrix4x4 &vec) const;

        // Divide
        // Matrix4x4& Matrix4x4::operator/=( Matrix4x4 &rhs);
        //  Matrix4x4 operator/( Matrix4x4 &vec);
        // Use % as dot product
        // Matrix4x4& Matrix4x4::operator%=( Matrix4x4 &rhs) = delete;
        // float operator%( Matrix4x4 &vec);
        // Equality
        bool operator==(const Matrix4x4 &other) const;
        bool operator!=(const Matrix4x4 &other) const;

        // Vector & T
        // Multiply
        Matrix4x4& operator*=(const float rhs);
        Matrix4x4 operator*(const float rhs) const;

        Vector4 operator*(const Vector4 &rhs) const;

        // Divide
        Matrix4x4& operator/=(const float rhs);
        Matrix4x4 operator/(const float rhs) const;

        // Standalone
        friend Matrix4x4 operator*(const float lhs, const Matrix4x4& rhs);

        // Out Streaming
        friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& vec);

        Matrix4x4 Transposed() const;
        Matrix4x4 Inversed() const;
        Matrix4x4 InverseTransposed() const;

        float Determinant() const;

        static Matrix4x4 TranslationMatrix(const Vector3& translation);
        static Matrix4x4 RotationMatrix(const Quaternion& rotation);
        static Matrix4x4 RotationYawPitchRollMatrix(const Vector3& yawPitchRoll);
        static Matrix4x4 ScaleMatrix(const Vector3& scale);

        static Matrix4x4 LookAtLH(const Vector3& pos, const Vector3& target, const Vector3& worldUp);

        static Matrix4x4 PerspectiveLHFOV(float fov, float aspect, float zNear, float zFar);
        static Matrix4x4 OrthographicPerspectiveLH(float viewWidth, float viewHeight, float zNear, float zFar);

    public:
        /**
         * @brief Variable that always is the 4x4 identity matrix.
         *
         */
        static Matrix4x4 s_Identity;
    };
}
