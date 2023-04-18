#include "FMath/Vector4.h"

#include <cmath>
#include <gsl/gsl>

#include <assert.h>

namespace Farlor
{
    Vector4::Vector4() noexcept
        : x {0}
        , y {0}
        , z {0}
        , w {0}
    {
    }

    Vector4::Vector4(float value) noexcept
        : x {value}
        , y {value}
        , z {value}
        , w {value}
    {
    }

    Vector4::Vector4(const float xNew, const float yNew, const float zNew, const float wNew) noexcept
        : x {xNew}
        , y {yNew}
        , z {zNew}
        , w {wNew}
    {
    }

    Vector4& Vector4::operator+=(const Vector4 &rhs) noexcept
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    Vector4 Vector4::operator+(const Vector4 &other) const noexcept
    {
        return Vector4(*this) += other;
    }

    Vector4& Vector4::operator-=(const Vector4 &rhs) noexcept
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }

    Vector4 Vector4::operator-(const Vector4 &other) const noexcept
    {
        return Vector4(*this) -= other;
    }

    Vector4& Vector4::operator*=(const Vector4 &rhs) noexcept
    {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        z *= rhs.w;
        return *this;
    }

    Vector4 Vector4::operator*(const Vector4 &other) const noexcept
    {
        return Vector4(*this) *= other;
    }

    Vector4& Vector4::operator/=(const Vector4 &rhs) noexcept
    {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        w /= rhs.w;
        return *this;
    }

    Vector4 Vector4::operator/(const Vector4 &other) const noexcept
    {
        return Vector4(*this) /= other;
    }

    bool Vector4::operator==(const Vector4 &other) const noexcept
    {
        return (x == other.x && y == other.y && z == other.z && w == other.w);
    }

    bool Vector4::operator!=(const Vector4 &other) const noexcept
    {
        return !(*this == other);
    }

    float& Vector4::operator[] (const int index) noexcept
    {
        return gsl::at(m_data, index);
    }

    const float& Vector4::operator[] (const int index) const
    {
        return gsl::at(m_data, index);
    }

    Vector4& Vector4::operator*=(const float& rhs) noexcept
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        w *= rhs;
        return *this;
    }

    Vector4 Vector4::operator*(const float& other) const noexcept
    {
        return Vector4(*this) *= other;
    }

    Vector4& Vector4::operator/=(const float &rhs) noexcept
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        w /= rhs;
        return *this;
    }

    Vector4 Vector4::operator/(const float &other) const noexcept
    {
        return Vector4(*this) /= other;
    }

    Vector4 operator*(const float lhs, const Vector4& rhs) noexcept
    {
        return Vector4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
    }

    std::ostream& operator<<(std::ostream& os, const Vector4& vec)
    {
        os << "<" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ">";
        return os;
    }

    float Vector4::Magnitude() const noexcept
    {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    float Vector4::SqrMagnitude() const noexcept
    {
        return x*x + y*y + z*z + w*w;
    }

    Vector4 Vector4::Normalized() const noexcept
    {
        const float mag = Magnitude();
        assert(mag != 0);

        return Vector4(x / mag, y / mag, z / mag, w / mag);
    }

    void Vector4::Normalize() noexcept
    {
        const float mag = Magnitude();
        assert(mag != 0);
        x /= mag;
        y /= mag;
        z /= mag;
        w /= mag;
    }

    float Vector4::Dot(const Vector4& other) const noexcept
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }
}
