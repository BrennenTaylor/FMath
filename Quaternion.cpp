#include "FMath/Quaternion.h"

#include <cmath>

using namespace std;

namespace Farlor
{
    Quaternion::Quaternion()
    {
        m_data[0] = 1.0f;
        m_data[1] = 0.0f;
        m_data[2] = 0.0f;
        m_data[3] = 0.0f;
    }

    Quaternion::Quaternion(float newS, Vector3 newU)
    {
        m_data[0] = newS;
        m_data[1] = newU.x;
        m_data[2] = newU.y;
        m_data[3] = newU.z;
    }

    Quaternion& Quaternion::operator+=(Quaternion &rhs)
    {
        m_data[0] += rhs.m_data[0];
        m_data[1] += rhs.m_data[1];
        m_data[2] += rhs.m_data[2];
        m_data[3] += rhs.m_data[3];
        return *this;
    }
    Quaternion Quaternion::operator+(Quaternion &other)
    {
        return Quaternion(*this) += other;
    }
    // Subtract
    Quaternion& Quaternion::operator-=(Quaternion &rhs)
    {
        m_data[0] -= rhs.m_data[0];
        m_data[1] -= rhs.m_data[1];
        m_data[2] -= rhs.m_data[2];
        m_data[3] -= rhs.m_data[3];
        return *this;
    }
    Quaternion Quaternion::operator-(Quaternion &other)
    {
        return Quaternion(*this) -= other;
    }
    // Multiply
    Quaternion& Quaternion::operator*=(Quaternion &rhs)
    {
        Farlor::Vector3 lhsU(m_data[1], m_data[2], m_data[3]);
        Farlor::Vector3 rhsU(rhs.m_data[1], rhs.m_data[2], rhs.m_data[3]);

        float newS = (m_data[0] * rhs.m_data[0]) - (lhsU.Dot(rhsU));
        Vector3 newU = m_data[0]*rhsU + rhs.m_data[0] * lhsU + lhsU.Cross(rhsU);
        m_data[0] = newS;
        m_data[1] = newU.x;
        m_data[2] = newU.y;
        m_data[3] = newU.z;
        return *this;
    }
    Quaternion Quaternion::operator*(Quaternion &other)
    {
        return Quaternion(*this) *= other;
    }

    // Equality
    bool Quaternion::operator==(Quaternion &other)
    {
        return (m_data[0] == other.m_data[0] && m_data[1] == other.m_data[1] && m_data[2] == other.m_data[2]  && m_data[3] == other.m_data[3] );
    }
    bool Quaternion::operator!=(Quaternion &other)
    {
        return !(*this == other);
    }

    // Vector & T
    // Multiply
    Quaternion& Quaternion::operator*=(float &rhs)
    {
        m_data[0] *= rhs;
        m_data[1] *= rhs;
        m_data[2] *= rhs;
        m_data[3] *= rhs;
        return *this;
    }
    Quaternion Quaternion::operator*(float &other)
    {
        return Quaternion(*this) *= other;
    }
    // Divide
    Quaternion& Quaternion::operator/=(float &rhs)
    {
        m_data[0] /= rhs;
        m_data[1] /= rhs;
        m_data[2] /= rhs;
        m_data[3] /= rhs;
        return *this;
    }
    Quaternion Quaternion::operator/(float &other)
    {
        return Quaternion(*this) /= other;
    }

    // Standalone
    Quaternion operator*(float lhs, Quaternion& rhs)
    {
        Farlor::Vector3 rhsU(rhs.m_data[1], rhs.m_data[2], rhs.m_data[3]);
        return Quaternion{lhs * rhs.m_data[0], lhs * rhsU};
    }

    // Out Streaming
    ostream& operator<<(ostream& os, Quaternion& quat)
    {
        os << "s: " << quat.m_data[0] << " u: <" << quat.m_data[1] << ", " << quat.m_data[2] << ", " << quat.m_data[3] << ">";
        return os;
    }

    // Local Math Operations
    float Quaternion::Magnitude()
    {
        return std::sqrt(m_data[0]*m_data[0] + m_data[1]*m_data[1] + m_data[2]*m_data[2] + m_data[3]*m_data[3]);
    }

    float Quaternion::SqrMagnitude()
    {
        return m_data[0]*m_data[0] + m_data[1]*m_data[1] + m_data[2]*m_data[2] + m_data[3]*m_data[3];
    }

    Quaternion Quaternion::Normalized()
    {
        float mag = Magnitude();

        if (mag == 0)
        {
            Quaternion result{*this};
            result.m_data[0] = 1.0f;
            return result;
        }

        Farlor::Vector3 lhsU(m_data[1], m_data[2], m_data[3]);
        return Quaternion {m_data[0] / mag, lhsU / mag};
    }

    void Quaternion::Normalize()
    {
        float mag = Magnitude();

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

    void Quaternion::RotateByVector(Vector3& vec)
    {
        Quaternion q(0.0f, vec);
        (*this) *= q;
    }

    void Quaternion::AddScaledVector(Vector3& vec, float scale)
    {
        Quaternion q(0, vec * scale);
        q *= (*this);
        m_data[0] += q.m_data[0] * 0.5f;
        m_data[1] += q.m_data[1] * 0.5f;
        m_data[2] += q.m_data[2] * 0.5f;
        m_data[3] += q.m_data[3] * 0.5f;
    }

    // http://answers.unity3d.com/questions/645903/please-explain-quaternions.html
    Quaternion Quaternion::RotationYawPitchRoll(float yaw, float pitch, float roll)
    {
        Quaternion rotation;
        float cy = cos(yaw * 0.5f);
        float sy = sin(yaw * 0.5f);
        float cr = cos(roll * 0.5f);
        float sr = sin(roll * 0.5f);
        float cp = cos(pitch * 0.5f);
        float sp = sin(pitch * 0.5f);

        rotation.m_data[0] = cy * cr * cp + sy * sr * sp;
        rotation.m_data[1] = cy * sr * cp - sy * cr * sp;
        rotation.m_data[2] = cy * cr * sp + sy * sr * cp;
        rotation.m_data[3] = sy * cr * cp - cy * sr * sp;
        return rotation;
    }

    Quaternion Quaternion::RotationAroundAxis(float angle, Vector3 axis)
    {
        Quaternion rotation;
        rotation.m_data[0] = std::cos(angle / 2.0f);
        
        Farlor::Vector3 tempU = std::sin(angle / 2.0f) * axis.Normalized(); 
        rotation.m_data[1] = tempU.x;
        rotation.m_data[2] = tempU.y;
        rotation.m_data[3] = tempU.z;
        return rotation;
    }
}
