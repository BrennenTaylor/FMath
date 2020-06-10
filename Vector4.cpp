#include "FMath/Vector4.h"

#include <assert.h>

namespace std
{
    template<> struct hash<Farlor::Vector4>
    {
        size_t operator()(const Farlor::Vector4& vector) const {
            size_t const h1(std::hash<float>{}(vector.x));
            size_t const h2(std::hash<float>{}(vector.y));
            size_t const h3(std::hash<float>{}(vector.z));
            size_t const h4(std::hash<float>{}(vector.w));
            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
        }
    };
}

namespace Farlor
{
    Vector4::Vector4()
        : x {0}
        , y {0}
        , z {0}
        , w {0}
    {
    }

    Vector4::Vector4(float value)
        : x {value}
        , y {value}
        , z {value}
        , w {value}
    {
    }

    Vector4::Vector4(const float xNew, const float yNew, const float zNew, const float wNew)
        : x {xNew}
        , y {yNew}
        , z {zNew}
        , w {wNew}
    {
    }

    Vector4& Vector4::operator+=(const Vector4 &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    Vector4 Vector4::operator+(const Vector4 &other) const
    {
        return Vector4(*this) += other;
    }

    Vector4& Vector4::operator-=(const Vector4 &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }

    Vector4 Vector4::operator-(const Vector4 &other) const
    {
        return Vector4(*this) -= other;
    }

    Vector4& Vector4::operator*=(const Vector4 &rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        z *= rhs.w;
        return *this;
    }

    Vector4 Vector4::operator*(const Vector4 &other) const
    {
        return Vector4(*this) *= other;
    }

    Vector4& Vector4::operator/=(const Vector4 &rhs)
    {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        w /= rhs.w;
        return *this;
    }

    Vector4 Vector4::operator/(const Vector4 &other) const
    {
        return Vector4(*this) /= other;
    }

    float Vector4::operator%(const Vector4 &other) const
    {
        return (*this).Dot(other);
    }

    bool Vector4::operator==(const Vector4 &other) const
    {
        return (x == other.x && y == other.y && z == other.z && w == other.w);
    }

    bool Vector4::operator!=(const Vector4 &other) const
    {
        return !(*this == other);
    }

    float& Vector4::operator[] (const int index)
    {
        return m_data[index];
    }

    const float& Vector4::operator[] (const int index) const
    {
        return m_data[index];
    }

    Vector4& Vector4::operator*=(const float& rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        w *= rhs;
        return *this;
    }

    Vector4 Vector4::operator*(const float& other) const
    {
        return Vector4(*this) *= other;
    }

    Vector4& Vector4::operator/=(const float &rhs)
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        w /= rhs;
        return *this;
    }

    Vector4 Vector4::operator/(const float &other) const
    {
        return Vector4(*this) /= other;
    }

    Vector4 operator*(const float lhs, const Vector4& rhs)
    {
        return Vector4{lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w};
    }

    std::ostream& operator<<(std::ostream& os, const Vector4& vec)
    {
        os << "<" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ">";
        return os;
    }

    float Vector4::Magnitude() const
    {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    float Vector4::SqrMagnitude() const
    {
        return x*x + y*y + z*z + w*w;
    }

    Vector4 Vector4::Normalized() const
    {
        float mag = Magnitude();
        assert(mag != 0);

        return Vector4 {x / mag, y / mag, z / mag, w / mag};
    }

    void Vector4::Normalize()
    {
        float mag = Magnitude();
        assert(mag != 0);
        x /= mag;
        y /= mag;
        z /= mag;
        w /= mag;
    }

    float Vector4::Dot(const Vector4& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }
}
