#include "FMath/Vector2.h"

#include <cmath>

#include <assert.h>

namespace Farlor
{
    Vector2::Vector2() noexcept
        : x {0}
        , y {0}
    {
    }

    Vector2::Vector2(float value) noexcept
        : x {value}
        , y {value}
    {
    }

    Vector2::Vector2(const float xNew, const float yNew) noexcept
        : x {xNew}
        , y {yNew}
    {
    }

    Vector2& Vector2::operator+=(const Vector2 &rhs) noexcept
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vector2 Vector2::operator+(const Vector2 &other) const noexcept
    {
        return Vector2(*this) += other;
    }

    Vector2& Vector2::operator-=(const Vector2 &rhs) noexcept
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vector2 Vector2::operator-(const Vector2 &other) const noexcept
    {
        return Vector2(*this) -= other;
    }

    Vector2& Vector2::operator*=(const Vector2 &rhs) noexcept
    {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    Vector2 Vector2::operator*(const Vector2 &other) const noexcept
    {
        return Vector2(*this) *= other;
    }

    Vector2& Vector2::operator/=(const Vector2 &rhs) noexcept
    {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }

    Vector2 Vector2::operator/(const Vector2 &other) const noexcept
    {
        return Vector2(*this) /= other;
    }

    bool Vector2::operator==(const Vector2 &other) const noexcept
    {
        return (x == other.x && y == other.y);
    }

    bool Vector2::operator!=(const Vector2 &other) const noexcept
    {
        return !(*this == other);
    }

    Vector2& Vector2::operator*=(const float& rhs) noexcept
    {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    Vector2 Vector2::operator*(const float& other) const noexcept
    {
        return Vector2(*this) *= other;
    }

    Vector2& Vector2::operator/=(const float &rhs) noexcept
    {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    Vector2 Vector2::operator/(const float &other) const noexcept
    {
        return Vector2(*this) /= other;
    }

    Vector2 operator*(const float lhs, const Vector2& rhs) noexcept
    {
        return Vector2(lhs * rhs.x, lhs * rhs.y);
    }

    std::ostream& operator<<(std::ostream& os, const Vector2& vec)
    {
        os << "<" << vec.x << ", " << vec.y << ">";
        return os;
    }

    float Vector2::Magnitude() const noexcept
    {
        return std::sqrt(x * x + y * y);
    }

    float Vector2::SqrMagnitude() const noexcept
    {
        return x*x + y*y;
    }

    Vector2 Vector2::Normalized() const noexcept
    {
        const float mag = Magnitude();
        assert(mag != 0);

        return Vector2 {x / mag, y / mag};
    }

    void Vector2::Normalize() noexcept
    {
        const float mag = Magnitude();
        assert(mag != 0);
        x /= mag;
        y /= mag;
    }

    float Vector2::Dot(const Vector2& other) const noexcept
    {
        return x * other.x + y * other.y;
    }
}
