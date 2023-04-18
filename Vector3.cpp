#include "FMath/Vector3.h"

#include <cmath>
#include <gsl/gsl>


namespace Farlor
{
    Vector3::Vector3() noexcept
        : m_data({0.0f, 0.0f, 0.0f})
    {
    }

    Vector3::Vector3(float value) noexcept
        : m_data({value, value, value})
    {
    }

    Vector3::Vector3( float xNew, float yNew, float zNew) noexcept
        : m_data({xNew, yNew, zNew})
    {
    }

    Vector3& Vector3::operator+=(const Vector3 &rhs) noexcept
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

     Vector3 Vector3::operator+(const Vector3 &other) const noexcept
    {
        return Vector3(*this) += other;
    }

    Vector3& Vector3::operator-=(const Vector3 &rhs) noexcept
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

     Vector3 Vector3::operator-(const Vector3 &other) const noexcept
    {
        return Vector3(*this) -= other;
    }

    Vector3& Vector3::operator*=(const Vector3 &rhs) noexcept
    {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        return *this;
    }

     Vector3 Vector3::operator*(const Vector3 &other) const noexcept
    {
        return Vector3(*this) *= other;
    }

    Vector3& Vector3::operator/=(const Vector3 &rhs) noexcept
    {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        return *this;
    }

    Vector3 Vector3::operator/(const Vector3 &other) const noexcept
    {
        return Vector3(*this) /= other;
    }

    bool Vector3::operator==(const Vector3 &other) const noexcept
    {
        return (x == other.x && y == other.y && z == other.z);
    }

    bool Vector3::operator!=(const Vector3 &other) const noexcept
    {
        return !(*this == other);
    }

    float& Vector3::operator[] (const int index) noexcept
    {
        return gsl::at(m_data, index);
    }

    Vector3& Vector3::operator*=(const float rhs) noexcept
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    Vector3 operator*(const Vector3& lhs, const float other) noexcept
    {
        return Vector3(lhs.x * other, lhs.y * other, lhs.z * other);
    }

    Vector3& Vector3::operator/=(const float rhs) noexcept
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }

    Vector3 operator/(const Vector3& lhs, float other) noexcept
    {
        return Vector3(lhs.x / other, lhs.y / other, lhs.z / other);
    }

    Vector3 operator*(const float lhs, const Vector3& rhs) noexcept
    {
        return Vector3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
    }

    std::ostream& operator<<(std::ostream& os, const Vector3& vec)
    {
        os << "<" << vec.x << ", " << vec.y << ", " << vec.z << ">";
        return os;
    }

    float Vector3::Magnitude() const noexcept
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    float Vector3::SqrMagnitude() const noexcept
    {
        return x*x + y*y + z*z;
    }

    Vector3 Vector3::Normalized() const noexcept
    {
        const float mag = Magnitude();
        if (mag == 0.0f)
            return Vector3(0.0f, 0.0f, 0.0f);

        return Vector3 {x / mag, y / mag, z / mag};
    }

    void Vector3::Normalize() noexcept
    {
        const float mag = Magnitude();

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

    float Vector3::Dot(const Vector3& other) const noexcept
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 Vector3::Cross(const Vector3& other) const noexcept
    {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }

    // // For RHS. Flip oer
    // void Vector3::MakeOrthonormalBasisRHS(Vector3& a, Vector3& b, Vector3& c) noexcept
    // {
    //     a.Normalize();
    //     c = a.Cross(b);
    //     if(c.SqrMagnitude() == 0.0)
    //         return;
    //     c.Normalize();
    //     b = c.Cross(a);
    // }
}
