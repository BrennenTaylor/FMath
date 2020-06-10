#include "FMath/Quaternion.h"

using namespace std;

namespace Farlor
{
    Quaternion::Quaternion()
    {
        s = 1.0f;
        u = Vector3(0.0f, 0.0f, 0.0f);
    }

    Quaternion::Quaternion(float newS, Vector3 newU)
    {
        s = newS;
        u = newU;
    }

    Quaternion& Quaternion::operator+=(Quaternion &rhs)
    {
        s += rhs.s;
        u += rhs.u;
        return *this;
    }
    Quaternion Quaternion::operator+(Quaternion &other)
    {
        return Quaternion(*this) += other;
    }
    // Subtract
    Quaternion& Quaternion::operator-=(Quaternion &rhs)
    {
        s -= rhs.s;
        u -= rhs.u;
        return *this;
    }
    Quaternion Quaternion::operator-(Quaternion &other)
    {
        return Quaternion(*this) -= other;
    }
    // Multiply
    Quaternion& Quaternion::operator*=(Quaternion &rhs)
    {
        float newS = (s * rhs.s) - (u.Dot(rhs.u));
        Vector3 newU = s*rhs.u + rhs.s * u + u.Cross(rhs.u);
        s = newS;
        u = newU;
        return *this;
    }
    Quaternion Quaternion::operator*(Quaternion &other)
    {
        return Quaternion(*this) *= other;
    }

    // Equality
    bool Quaternion::operator==(Quaternion &other)
    {
        return (s == other.s && u == other.u);
    }
    bool Quaternion::operator!=(Quaternion &other)
    {
        return !(*this == other);
    }

    // Vector & T
    // Multiply
    Quaternion& Quaternion::operator*=(float &rhs)
    {
        s *= rhs;
        u *= rhs;
        return *this;
    }
    Quaternion Quaternion::operator*(float &other)
    {
        return Quaternion(*this) *= other;
    }
    // Divide
    Quaternion& Quaternion::operator/=(float &rhs)
    {
        s /= rhs;
        u /= rhs;
        return *this;
    }
    Quaternion Quaternion::operator/(float &other)
    {
        return Quaternion(*this) /= other;
    }

    // Standalone
    Quaternion operator*(float lhs, Quaternion& rhs)
    {
        return Quaternion{lhs * rhs.s, lhs * rhs.u};
    }

    // Out Streaming
    ostream& operator<<(ostream& os, Quaternion& quat)
    {
        os << "s: " << quat.s << " u: <" << quat.u << ">";
        return os;
    }

    // Local Math Operations
    float Quaternion::Magnitude()
    {
        return sqrt(s*s + u.x*u.x + u.y*u.y + u.z*u.z);
    }

    float Quaternion::SqrMagnitude()
    {
        return s*s + u.x*u.x + u.y*u.y + u.z*u.z;
    }

    Quaternion Quaternion::Normalized()
    {
        float mag = Magnitude();

        if (mag == 0)
        {
            Quaternion result{*this};
            result.s = 1.0f;
            return result;
        }

        return Quaternion {s / mag, u / mag};
    }

    void Quaternion::Normalize()
    {
        float mag = Magnitude();

        if (mag == 0)
        {
            s = 1.0f;
            return;
        }

        s /= mag;
        u /= mag;
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
        s += q.s * 0.5f;
        u.x += q.u.x * 0.5f;
        u.y += q.u.y * 0.5f;
        u.z += q.u.z * 0.5f;
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

        rotation.s = cy * cr * cp + sy * sr * sp;
        rotation.u.x = cy * sr * cp - sy * cr * sp;
        rotation.u.y = cy * cr * sp + sy * sr * cp;
        rotation.u.z = sy * cr * cp - cy * sr * sp;
        return rotation;
    }

    Quaternion Quaternion::RotationAroundAxis(float angle, Vector3 axis)
    {
        Quaternion rotation;
        rotation.s = std::cos(angle / 2.0f);
        rotation.u = std::sin(angle / 2.0f) * axis.Normalized();
        return rotation;
    }
}
