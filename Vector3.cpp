#include "FMath/Vector3.h"

#include <cmath>

namespace Farlor
{
    Vector3::Vector3()
        : x {0}
        , y {0}
        , z {0}
    {
    }

    Vector3::Vector3(float value)
        : x {value}
        , y {value}
        , z {value}
    {
    }

    Vector3::Vector3( float xNew,  float yNew,  float zNew)
        : x {xNew}
        , y {yNew}
        , z {zNew}
    {
    }

    Vector3& Vector3::operator+=(const Vector3 &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

     Vector3 Vector3::operator+(const Vector3 &other) const
    {
        return Vector3(*this) += other;
    }

    Vector3& Vector3::operator-=(const Vector3 &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

     Vector3 Vector3::operator-(const Vector3 &other) const
    {
        return Vector3(*this) -= other;
    }

    Vector3& Vector3::operator*=(const Vector3 &rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        return *this;
    }

     Vector3 Vector3::operator*(const Vector3 &other) const
    {
        return Vector3(*this) *= other;
    }

    Vector3& Vector3::operator/=(const Vector3 &rhs)
    {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        return *this;
    }

    Vector3 Vector3::operator/(const Vector3 &other) const
    {
        return Vector3(*this) /= other;
    }

    float Vector3::operator%(const Vector3 &other) const
    {
        return Vector3(*this).Dot(other);
    }

    bool Vector3::operator==(const Vector3 &other) const
    {
        return (x == other.x && y == other.y && z == other.z);
    }

    bool Vector3::operator!=(const Vector3 &other) const
    {
        return !(*this == other);
    }

    float& Vector3::operator[] (const int index)
    {
        return m_data[index];
    }

    Vector3& Vector3::operator*=(const float& rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    Vector3 operator*(const Vector3 lhs, const float& other)
    {
        return Vector3(lhs.x * other, lhs.y * other, lhs.z * other);
    }

    Vector3& Vector3::operator/=( float &rhs)
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }

    Vector3 operator/(const Vector3 lhs, float &other)
    {
        return Vector3(lhs.x / other, lhs.y / other, lhs.z / other);
    }

    Vector3 operator*(const float lhs, const Vector3& rhs)
    {
        return Vector3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
    }

    std::ostream& operator<<(std::ostream& os, const Vector3& vec)
    {
        os << "<" << vec.x << ", " << vec.y << ", " << vec.z << ">";
        return os;
    }

    float Vector3::Magnitude() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    float Vector3::SqrMagnitude() const
    {
        return x*x + y*y + z*z;
    }

    Vector3 Vector3::Normalized() const
    {
        float mag = Magnitude();
        if (mag == 0.0f)
            return Vector3(0.0f, 0.0f, 0.0f);

        return Vector3 {x / mag, y / mag, z / mag};
    }

    void Vector3::Normalize()
    {
        float mag = Magnitude();

        if (mag == 0.0f)
        {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
            return;
        }

        x /= mag;
        y /= mag;
        z /= mag;
    }

    float Vector3::Dot(const Vector3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 Vector3::Cross(const Vector3& other) const
    {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }

    void Vector3::AddScaledVector(const Vector3& other, const float scaler)
    {
        x += other.x * scaler;
        y += other.y * scaler;
        z += other.z * scaler;
    }

    // For RHS. Flip oer
    void MakeOrthonormalBasisRHS(Vector3& a, Vector3& b, Vector3& c)
    {
        a.Normalize();
        c = a.Cross(b);
        if(c.SqrMagnitude() == 0.0)
            return;
        c.Normalize();
        b = c.Cross(a);
    }
}
