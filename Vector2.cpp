#include "FMath/Vector2.h"

#include <assert.h>

namespace std
{
    template<> struct hash<Farlor::Vector2>
    {
        size_t operator()(const Farlor::Vector2& vector) const {
            size_t const h1(std::hash<float>{}(vector.x));
            size_t const h2(std::hash<float>{}(vector.y));
            return h1 ^ (h2 << 1);
        }
    };
}

namespace Farlor
{
    Vector2::Vector2()
        : x {0}
        , y {0}
    {
    }

    Vector2::Vector2(float value)
        : x {value}
        , y {value}
    {
    }

    Vector2::Vector2(const float xNew, const float yNew)
        : x {xNew}
        , y {yNew}
    {
    }

    Vector2& Vector2::operator+=(const Vector2 &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vector2 Vector2::operator+(const Vector2 &other) const
    {
        return Vector2(*this) += other;
    }

    Vector2& Vector2::operator-=(const Vector2 &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vector2 Vector2::operator-(const Vector2 &other) const
    {
        return Vector2(*this) -= other;
    }

    Vector2& Vector2::operator*=(const Vector2 &rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    Vector2 Vector2::operator*(const Vector2 &other) const
    {
        return Vector2(*this) *= other;
    }

    Vector2& Vector2::operator/=(const Vector2 &rhs)
    {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }

    Vector2 Vector2::operator/(const Vector2 &other) const
    {
        return Vector2(*this) /= other;
    }

    float Vector2::operator%(const Vector2 &other) const
    {
        return (*this).Dot(other);
    }

    bool Vector2::operator==(const Vector2 &other) const
    {
        return (x == other.x && y == other.y);
    }

    bool Vector2::operator!=(const Vector2 &other) const
    {
        return !(*this == other);
    }

    Vector2& Vector2::operator*=(const float& rhs)
    {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    Vector2 Vector2::operator*(const float& other) const
    {
        return Vector2(*this) *= other;
    }

    Vector2& Vector2::operator/=(const float &rhs)
    {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    Vector2 Vector2::operator/(const float &other) const
    {
        return Vector2(*this) /= other;
    }

    Vector2 operator*(const float lhs, const Vector2& rhs)
    {
        return Vector2(lhs * rhs.x, lhs * rhs.y);
    }

    std::ostream& operator<<(std::ostream& os, const Vector2& vec)
    {
        os << "<" << vec.x << ", " << vec.y << ">";
        return os;
    }

    float Vector2::Magnitude() const
    {
        return std::sqrt(x * x + y * y);
    }

    float Vector2::SqrMagnitude() const
    {
        return x*x + y*y;
    }

    Vector2 Vector2::Normalized() const
    {
        float mag = Magnitude();
        assert(mag != 0);

        return Vector2 {x / mag, y / mag};
    }

    void Vector2::Normalize()
    {
        float mag = Magnitude();
        assert(mag != 0);
        x /= mag;
        y /= mag;
    }

    float Vector2::Dot(const Vector2& other) const
    {
        return x * other.x + y * other.y;
    }
}
