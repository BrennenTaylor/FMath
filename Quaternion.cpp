#include "FMath/Quaternion.h"

#include <cmath>

using namespace std;

namespace Farlor
{
    Quaternion::Quaternion() noexcept
    {
        m_data[0] = 1.0f;
        m_data[1] = 0.0f;
        m_data[2] = 0.0f;
        m_data[3] = 0.0f;
    }

    Quaternion::Quaternion(const float newS, const float newUx, const float newUy, const float newUz) noexcept
    {
        m_data[0] = newS;
        m_data[1] = newUx;
        m_data[2] = newUy;
        m_data[3] = newUz;
    }

    Quaternion::Quaternion(float newS, const Vector3& newU) noexcept
    {
        m_data[0] = newS;
        m_data[1] = newU.x;
        m_data[2] = newU.y;
        m_data[3] = newU.z;
    }

    Quaternion& Quaternion::operator+=(const Quaternion &rhs) noexcept
    {
        m_data[0] += rhs.m_data[0];
        m_data[1] += rhs.m_data[1];
        m_data[2] += rhs.m_data[2];
        m_data[3] += rhs.m_data[3];
        return *this;
    }
    Quaternion Quaternion::operator+(const Quaternion &other) const noexcept
    {
        return Quaternion(*this) += other;
    }
    // Subtract
    Quaternion& Quaternion::operator-=(const Quaternion &rhs) noexcept
    {
        m_data[0] -= rhs.m_data[0];
        m_data[1] -= rhs.m_data[1];
        m_data[2] -= rhs.m_data[2];
        m_data[3] -= rhs.m_data[3];
        return *this;
    }
    Quaternion Quaternion::operator-(const Quaternion &other) const noexcept
    {
        return Quaternion(*this) -= other;
    }
    // Multiply
    Quaternion& Quaternion::operator*=(const Quaternion &rhs) noexcept
    {
        const Farlor::Vector3 lhsU(m_data[1], m_data[2], m_data[3]);
        const Farlor::Vector3 rhsU(rhs.m_data[1], rhs.m_data[2], rhs.m_data[3]);

        const float newS = (m_data[0] * rhs.m_data[0]) - (lhsU.Dot(rhsU));
        const Vector3 newU = m_data[0]*rhsU + rhs.m_data[0] * lhsU + lhsU.Cross(rhsU);
        m_data[0] = newS;
        m_data[1] = newU.x;
        m_data[2] = newU.y;
        m_data[3] = newU.z;
        return *this;
    }
    Quaternion Quaternion::operator*(const Quaternion &other) const noexcept
    {
        return Quaternion(*this) *= other;
    }

    // Equality
    bool Quaternion::operator==(const Quaternion& other) const noexcept
    {
        return (m_data[0] == other.m_data[0] && m_data[1] == other.m_data[1] && m_data[2] == other.m_data[2]  && m_data[3] == other.m_data[3] );
    }
    bool Quaternion::operator!=(const Quaternion& other) const noexcept
    {
        return !(*this == other);
    }

    // Vector & T
    // Multiply
    Quaternion& Quaternion::operator*=(const float rhs) noexcept
    {
        m_data[0] *= rhs;
        m_data[1] *= rhs;
        m_data[2] *= rhs;
        m_data[3] *= rhs;
        return *this;
    }
    Quaternion Quaternion::operator*(const float other) const noexcept
    {
        return Quaternion(*this) *= other;
    }
    // Divide
    Quaternion& Quaternion::operator/=(const float rhs) noexcept
    {
        m_data[0] /= rhs;
        m_data[1] /= rhs;
        m_data[2] /= rhs;
        m_data[3] /= rhs;
        return *this;
    }
    Quaternion Quaternion::operator/(const float other) const noexcept
    {
        return Quaternion(*this) /= other;
    }

    // Standalone
    Quaternion operator*(float lhs, Quaternion& rhs) noexcept
    {
        const Farlor::Vector3 rhsU(rhs.m_data[1], rhs.m_data[2], rhs.m_data[3]);
        return Quaternion{lhs * rhs.m_data[0], lhs * rhsU};
    }

    // Out Streaming
    ostream& operator<<(ostream& os, Quaternion& quat)
    {
        os << "s: " << quat.m_data[0] << " u: <" << quat.m_data[1] << ", " << quat.m_data[2] << ", " << quat.m_data[3] << ">";
        return os;
    }

    // Local Math Operations
    float Quaternion::Magnitude() const noexcept
    {
        return std::sqrt(m_data[0]*m_data[0] + m_data[1]*m_data[1] + m_data[2]*m_data[2] + m_data[3]*m_data[3]);
    }

    float Quaternion::SqrMagnitude() const noexcept
    {
        return m_data[0]*m_data[0] + m_data[1]*m_data[1] + m_data[2]*m_data[2] + m_data[3]*m_data[3];
    }

    Quaternion Quaternion::Normalized() const noexcept
    {
        const float mag = Magnitude();

        if (mag == 0)
        {
            Quaternion result{*this};
            result.m_data[0] = 1.0f;
            return result;
        }

        const Farlor::Vector3 lhsU(m_data[1], m_data[2], m_data[3]);
        return Quaternion {m_data[0] / mag, lhsU / mag};
    }

    void Quaternion::Normalize() noexcept
    {
        const float mag = Magnitude();

        if (mag == 0)
        {
            m_data[0] = 1.0f;
            return;
        }

        m_data[0] /= mag;
        m_data[1] /= mag;
        m_data[2] /= mag;
        m_data[3] /= mag;
    }

    void Quaternion::RotateByVector(const Vector3& vec) noexcept
    {
        const Quaternion q(0.0f, vec);
        (*this) *= q;
    }

    void Quaternion::AddScaledVector(const Vector3& vec, float scale) noexcept
    {
        Quaternion q(0, vec * scale);
        q *= (*this);
        m_data[0] += q.m_data[0] * 0.5f;
        m_data[1] += q.m_data[1] * 0.5f;
        m_data[2] += q.m_data[2] * 0.5f;
        m_data[3] += q.m_data[3] * 0.5f;
    }

    // http://answers.unity3d.com/questions/645903/please-explain-quaternions.html
    Quaternion Quaternion::RotationYawPitchRoll(float yaw, float pitch, float roll) noexcept
    {
        const float cy = cos(yaw * 0.5f);
        const float sy = sin(yaw * 0.5f);
        const float cr = cos(roll * 0.5f);
        const float sr = sin(roll * 0.5f);
        const float cp = cos(pitch * 0.5f);
        const float sp = sin(pitch * 0.5f);

        Quaternion rotation (
            cy * cr * cp + sy * sr * sp,
            cy * sr * cp - sy * cr * sp,
            cy * cr * sp + sy * sr * cp,
            sy * cr * cp - cy * sr * sp
        );
        return rotation;
    }

    Quaternion Quaternion::RotationAroundAxis(float angle, const Vector3& axis) noexcept
    {
        Quaternion rotation;
        rotation.m_data[0] = std::cos(angle / 2.0f);
        
        const Farlor::Vector3 tempU = std::sin(angle / 2.0f) * axis.Normalized(); 
        rotation.m_data[1] = tempU.x;
        rotation.m_data[2] = tempU.y;
        rotation.m_data[3] = tempU.z;
        return rotation;
    }
}
