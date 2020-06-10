#include "FMath/Matrix2x2.h"

#include <assert.h>

namespace Farlor
{
    const Matrix2x2 Matrix2x2::s_Identity = Matrix2x2(Vector2(1.0f, 0.0f), Vector2(0.0f, 1.0f));

    Matrix2x2::Matrix2x2()
    {
        m_rows[0] = s_Identity.m_rows[0];
        m_rows[1] = s_Identity.m_rows[1];
    }

    Matrix2x2::Matrix2x2(Vector2 row0, Vector2 row1)
    {
        m_rows[0] = row0;
        m_rows[1] = row1;
    }

    Matrix2x2& Matrix2x2::operator+=(const Matrix2x2 &rhs)
    {
        m_rows[0] += rhs.m_rows[0];
        m_rows[1] += rhs.m_rows[1];
        return *this;
    }

    Matrix2x2 Matrix2x2::operator+(const Matrix2x2 &other) const
    {
        return Matrix2x2(*this) += other;
    }

    Matrix2x2& Matrix2x2::operator-=(const Matrix2x2 &rhs)
    {
        m_rows[0] -= rhs.m_rows[0];
        m_rows[1] -= rhs.m_rows[1];
        return *this;
    }

    Matrix2x2 Matrix2x2::operator-(const Matrix2x2 &other) const
    {
        return Matrix2x2(*this) -= other;
    }

    Matrix2x2& Matrix2x2::Matrix2x2::operator*=(const Matrix2x2 &rhs)
    {
        Vector2 newRow0;
        Vector2 newRow1;
        newRow0.x = m_r1c1 * rhs.m_r1c1 + m_r1c2 * rhs.m_r2c1;
        newRow0.y = m_r1c1 * rhs.m_r1c2 + m_r1c2 * rhs.m_r2c2;
        newRow1.x = m_r2c1 * rhs.m_r1c1 + m_r2c2 * rhs.m_r2c1;
        newRow1.y = m_r2c1 * rhs.m_r1c2 + m_r2c2 * rhs.m_r2c2;
        m_rows[0] = newRow0;
        m_rows[1] = newRow1;
        return *this;
    }

    Matrix2x2 Matrix2x2::operator*(const Matrix2x2 &other) const
    {
        return Matrix2x2(*this) *= other;
    }

    bool Matrix2x2::operator==(const Matrix2x2 &other) const
    {
        return (m_rows[0] == other.m_rows[0]) && (m_rows[1] == other.m_rows[1]);
    }

    bool Matrix2x2::operator!=(const Matrix2x2 &other) const
    {
        return !(*this == other);
    }

    Matrix2x2& Matrix2x2::operator*=( float &rhs)
    {
        m_rows[0] *= rhs;
        m_rows[1] *= rhs;
        return (*this);
    }

    Matrix2x2 Matrix2x2::operator*( float &rhs) const
    {
        return Matrix2x2(*this) *= rhs;
    }

    Vector2 Matrix2x2::operator*(const Vector2 &rhs) const
    {
        Vector2 val;
        val.x = m_rows[0].Dot(rhs);
        val.y = m_rows[1].Dot(rhs);
        return val;
    }

    Matrix2x2& Matrix2x2::operator/=( float &rhs)
    {
        m_rows[0] /= rhs;
        m_rows[1] /= rhs;
        return (*this);
    }

    Matrix2x2 Matrix2x2::operator/( float &rhs) const
    {
        return Matrix2x2(*this) /= rhs;
    }

    Matrix2x2 operator*(float lhs, const Matrix2x2& rhs)
    {
        return Matrix2x2(lhs * rhs.m_rows[0], lhs * rhs.m_rows[1]);
    }

    std::ostream& operator<<(std::ostream& os, Matrix2x2& mat)
    {
        os << mat.m_rows[0] << mat.m_rows[1] << std::endl;
        return os;
    }

    Matrix2x2 Matrix2x2::Inversed() const
    {
        assert(false);
        return s_Identity;
    }

    Matrix2x2 Matrix2x2::Transposed() const
    {
        Matrix2x2 val(*this);
        float temp = 0.0f;
        temp = val.m_r1c2;
        val.m_r1c2 = val.m_r2c1;
        val.m_r2c1 = temp;
        return val;
    }
}
