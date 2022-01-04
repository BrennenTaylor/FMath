#pragma once

#include "Vector3.h"
#include "Vector4.h"

#include <iostream>

/**
 * @brief The farlor 3d graphics libraries
*/
namespace Farlor
{
    /**
     * @brief Class which represents a quaternion rotation
     *
     */
    class Quaternion
    {
    public:
        union
        {
            float m_data[4];
        };

        Quaternion() noexcept;
        Quaternion(const float newS, const float newUx, const float newUy, const float newUz) noexcept;
        Quaternion(const float newS, const Vector3& newU) noexcept;

        // Quaternion & Quaternion
        // Add
        Quaternion& operator+=(const Quaternion &rhs) noexcept;
        Quaternion operator+(const Quaternion &vec) const noexcept;
        // Subtract
        Quaternion& operator-=(const Quaternion &rhs) noexcept;
        Quaternion operator-(const Quaternion &vec) const noexcept;
        // Multiply
        Quaternion& operator*=(const Quaternion &rhs) noexcept;
        Quaternion operator*(const Quaternion &vec) const noexcept;
        // Divide
        Quaternion& operator/=(const Quaternion &rhs) noexcept;
        Quaternion operator/(const Quaternion &vec) const noexcept;

        // Equality
        bool operator==(const Quaternion &other) const noexcept;
        bool operator!=(const Quaternion &other) const noexcept;

        // Vector & T
        // Multiply
        Quaternion& operator*=(const float rhs) noexcept;
        Quaternion operator*(const float rhs) const noexcept;
        // Divide
        Quaternion& operator/=(const float rhs) noexcept;
        Quaternion operator/(const float rhs) const noexcept;

        // Standalone
        friend Quaternion operator*(float lhs, const Quaternion& rhs) noexcept;

        // Out Streaming
        friend std::ostream& operator<<(std::ostream& os, Quaternion& vec);

        // Local Math Operations
        float Magnitude() const noexcept;
        float SqrMagnitude() const noexcept;
        Quaternion Normalized() const noexcept;
        void Normalize() noexcept;

        void RotateByVector(const Vector3& vec) noexcept;
        void AddScaledVector(const Vector3& vec, float scale) noexcept;

        static Quaternion RotationYawPitchRoll(float x, float y, float z) noexcept;
        static Quaternion RotationAroundAxis(float angle, const Vector3& axis) noexcept;
    };
}
