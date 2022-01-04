#include "FMath/Matrix3x3.h"

#ifdef WIN32
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#endif

#include <glm/mat3x3.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef WIN32
#pragma warning(pop)
#endif

#include <gsl/gsl>

namespace Farlor
{
    Matrix3x3 Matrix3x3::s_Identity = Matrix3x3(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));

    Matrix3x3::Matrix3x3() noexcept
        : m_data({0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f})
        , m_r0c0(gsl::at(m_data, 0))
        , m_r0c1(gsl::at(m_data, 1))
        , m_r0c2(gsl::at(m_data, 2))
        , m_r1c0(gsl::at(m_data, 3))
        , m_r1c1(gsl::at(m_data, 4))
        , m_r1c2(gsl::at(m_data, 5))
        , m_r2c0(gsl::at(m_data, 6))
        , m_r2c1(gsl::at(m_data, 7))
        , m_r2c2(gsl::at(m_data, 8))
    {
    }

    Matrix3x3::Matrix3x3(Vector3 row0, Vector3 row1, Vector3 row2) noexcept
        : m_data({row0.x, row0.y, row0.z, row1.x, row1.y, row1.z, row2.x, row2.y, row2.z})
        , m_r0c0(gsl::at(m_data, 0))
        , m_r0c1(gsl::at(m_data, 1))
        , m_r0c2(gsl::at(m_data, 2))
        , m_r1c0(gsl::at(m_data, 3))
        , m_r1c1(gsl::at(m_data, 4))
        , m_r1c2(gsl::at(m_data, 5))
        , m_r2c0(gsl::at(m_data, 6))
        , m_r2c1(gsl::at(m_data, 7))
        , m_r2c2(gsl::at(m_data, 8))
    {
    }

    Matrix3x3::Matrix3x3(Quaternion q) noexcept
        : m_r0c0(gsl::at(m_data, 0))
        , m_r0c1(gsl::at(m_data, 1))
        , m_r0c2(gsl::at(m_data, 2))
        , m_r1c0(gsl::at(m_data, 3))
        , m_r1c1(gsl::at(m_data, 4))
        , m_r1c2(gsl::at(m_data, 5))
        , m_r2c0(gsl::at(m_data, 6))
        , m_r2c1(gsl::at(m_data, 7))
        , m_r2c2(gsl::at(m_data, 8))
    {
        m_r0c0 = 1 - 2 * q.m_data[2]*q.m_data[2] - 2*q.m_data[3]*q.m_data[3];
        m_r0c1 = 2 * q.m_data[1]*q.m_data[2] - 2*q.m_data[0] *q.m_data[3];
        m_r0c2 = 2 * q.m_data[1]*q.m_data[3] + 2*q.m_data[0] *q.m_data[2];

        m_r1c0 = 2 * q.m_data[1]*q.m_data[2] + 2*q.m_data[0] *q.m_data[3];
        m_r1c1 = 1 - 2*q.m_data[1]*q.m_data[1] - 2*q.m_data[3]*q.m_data[3];
        m_r1c2 = 2 * q.m_data[2]*q.m_data[3] - 2*q.m_data[0] *q.m_data[1];

        m_r2c0 = 2 * q.m_data[1]*q.m_data[3] - 2*q.m_data[0] *q.m_data[2];
        m_r2c1 = 2 * q.m_data[2]*q.m_data[3] + 2*q.m_data[0] *q.m_data[1];
        m_r2c2 = 1 - 2*q.m_data[1]*q.m_data[1] - 2*q.m_data[2]*q.m_data[2];
    }

    // Matrix3x3 & Matrix3x3
    // Add
    Matrix3x3& Matrix3x3::operator+=(const Matrix3x3 &rhs) noexcept
    {
        m_rows[0] += rhs.m_rows[0];
        m_rows[1] += rhs.m_rows[1];
        m_rows[2] += rhs.m_rows[2];
        return *this;
    }
    Matrix3x3 Matrix3x3::operator+(const Matrix3x3 &other) const noexcept
    {
        return Matrix3x3(*this) += other;
    }
    // Subtract
    Matrix3x3& Matrix3x3::operator-=(const Matrix3x3 &rhs) noexcept
    {
        for (size_t elemIdx = 0; elemIdx < m_data.size(); elemIdx++)
        {
            gsl::at(m_data, elemIdx) /= gsl::at(rhs.m_data, elemIdx);
        }
        return *this;
    }
    Matrix3x3 Matrix3x3::operator-(const Matrix3x3 &other) const noexcept
    {
        return Matrix3x3(*this) -= other;
    }
    // Multiply
    // r1c1 r1c2 r1c3
    // r2c1 r2c2 r2c3
    // r3c1 r3c2 r3c3
    Matrix3x3& Matrix3x3::Matrix3x3::operator*=(const Matrix3x3 &rhs) noexcept
    {
        m_r0c0 = m_r0c0 * rhs.m_r0c0 + m_r0c1 * rhs.m_r1c0 + m_r0c2 * rhs.m_r2c0;
        m_r0c1 = m_r0c0 * rhs.m_r0c1 + m_r0c1 * rhs.m_r1c1 + m_r0c2 * rhs.m_r2c1;
        m_r0c2 = m_r0c0 * rhs.m_r0c2 + m_r0c1 * rhs.m_r1c2 + m_r0c2 * rhs.m_r2c2;

        m_rows[1] = Vector3(
            m_r1c0 * rhs.m_r0c0 + m_r1c1 * rhs.m_r1c0 + m_r1c2 * rhs.m_r2c0,
            m_r1c0 * rhs.m_r0c1 + m_r1c1 * rhs.m_r1c1 + m_r1c2 * rhs.m_r2c1,
            m_r1c0 * rhs.m_r0c2 + m_r1c1 * rhs.m_r1c2 + m_r1c2 * rhs.m_r2c2
        );
        m_rows[2] = Vector3(
            m_r2c0 * rhs.m_r0c0 + m_r2c1 * rhs.m_r1c0 + m_r2c2 * rhs.m_r2c0,
            m_r2c0 * rhs.m_r0c1 + m_r2c1 * rhs.m_r1c1 + m_r2c2 * rhs.m_r2c1,
            m_r2c0 * rhs.m_r0c2 + m_r2c1 * rhs.m_r1c2 + m_r2c2 * rhs.m_r2c2
        );
        return (*this);
    }
    Matrix3x3 Matrix3x3::operator*(const Matrix3x3 &other) const noexcept
    {
        return Matrix3x3(*this) *= other;
    }

    // Equality
    bool Matrix3x3::operator==(const Matrix3x3 &other) const noexcept
    {
        bool equal = true;
        for (size_t idx = 0; idx < m_data.size(); idx++)
        {
            equal = equal & (gsl::at(m_data, idx) == gsl::at(other.m_data, idx));
        }
        return equal;
    }

    bool Matrix3x3::operator!=(const Matrix3x3 &other) const noexcept
    {
        return !(*this == other);
    }

    // Vector & T
    // Multiply
    Matrix3x3& Matrix3x3::operator*=( float &rhs) noexcept
    {
        for (auto& element : m_data)
        {
            element *= rhs;
        }
        return (*this);
    }
    Matrix3x3 Matrix3x3::operator*( float &rhs) const noexcept
    {
        return Matrix3x3(*this) *= rhs;
    }

    Vector3 Matrix3x3::operator*(const Vector3 &rhs) const noexcept
    {
        Vector3 val;
        val.x = m_rows[0].Dot(rhs);
        val.y = m_rows[1].Dot(rhs);
        val.z = m_rows[2].Dot(rhs);
        return val;
    }

    // Divide
    Matrix3x3& Matrix3x3::operator/=( float &rhs) noexcept
    {
        for (auto& element : m_data)
        {
            element /= rhs;
        }
        return (*this);
    }
    Matrix3x3 Matrix3x3::operator/( float &rhs) const noexcept
    {
        return Matrix3x3(*this) /= rhs;
    }

    // Standalone
    Matrix3x3 operator*(float lhs, const Matrix3x3& rhs) noexcept
    {
        return Matrix3x3(lhs * rhs.m_rows[0], lhs * rhs.m_rows[1], lhs * rhs.m_rows[2]);
    }

    // Out Streaming
    std::ostream& operator<<(std::ostream& os, Matrix3x3& mat)
    {
        os << mat.m_rows[0] << mat.m_rows[1] << mat.m_rows[2];
        return os;
    }

    Matrix3x3 Matrix3x3::Inversed() const
    {
        Matrix3x3 val(*this);

        glm::mat3 tempMatrix = {
            val.m_r0c0, val.m_r0c1, val.m_r0c2,
            val.m_r1c0, val.m_r1c1, val.m_r1c2,
            val.m_r2c0, val.m_r2c1, val.m_r2c2,
        };
        // Flip as we are row major and glm is column major
        tempMatrix = glm::transpose(tempMatrix);
        tempMatrix = glm::inverse(tempMatrix);
        // Flip back
        tempMatrix = glm::transpose(tempMatrix);

        val.m_r0c0 = tempMatrix[0].x;
        val.m_r0c1 = tempMatrix[0].y;
        val.m_r0c2 = tempMatrix[0].z;

        val.m_r1c0 = tempMatrix[1].x;
        val.m_r1c1 = tempMatrix[1].y;
        val.m_r1c2 = tempMatrix[1].z;

        val.m_r2c0 = tempMatrix[2].x;
        val.m_r2c1 = tempMatrix[2].y;
        val.m_r2c2 = tempMatrix[2].z;

        return val;
    }

    Matrix3x3 Matrix3x3::Transposed() const noexcept
    {
        Matrix3x3 val(*this);
        std::swap(val.m_r0c1, val.m_r1c0);
        std::swap(val.m_r0c2, val.m_r2c0);
        std::swap(val.m_r1c2, val.m_r2c1);
        return val;
    }

    Quaternion Matrix3x3::ConvertToQuaternion(Matrix3x3& mat)
    {
        Quaternion result;

        float r = 0.0;
        const float t = mat.m_r0c0 + mat.m_r1c1 + mat.m_r2c2;

        if (t >= 0.0f)
        {
            r = std::sqrt(t+1);
            result.m_data[0]  = r/2.0f;
            result.m_data[1] = (mat.m_rows[2][1] - mat.m_rows[1][2])/(2.0f*r);
            result.m_data[2] = (mat.m_rows[0][2] - mat.m_rows[2][0])/(2.0f*r);
            result.m_data[3] = (mat.m_rows[1][0] - mat.m_rows[0][1])/(2.0f*r);
        }
        else if (mat.m_rows[0][0] > mat.m_rows[1][1] && mat.m_rows[0][0] > mat.m_rows[2][2])
        {
            r = std::sqrt(mat.m_rows[0][0] - (mat.m_rows[1][1] + mat.m_rows[2][2]) + 1);
            result.m_data[1] = r/2.0f;
            result.m_data[2] = (mat.m_rows[0][1] - mat.m_rows[1][0])/(2.0f*r);
            result.m_data[3] = (mat.m_rows[2][0] - mat.m_rows[0][2])/(2.0f*r);
            result.m_data[0]  = (mat.m_rows[2][1] - mat.m_rows[1][2])/(2.0f*r);
        }
        else if (mat.m_rows[1][1] > mat.m_rows[0][0] && mat.m_rows[1][1] > mat.m_rows[2][2])
        {
            r = std::sqrt(mat.m_rows[1][1] - (mat.m_rows[2][2] + mat.m_rows[0][0]) + 1);
            result.m_data[2] = r/2.0f;
            result.m_data[3] = (mat.m_rows[1][2] - mat.m_rows[2][1])/(2.0f*r);
            result.m_data[1] = (mat.m_rows[0][1] - mat.m_rows[1][0])/(2.0f*r);
            result.m_data[0]  = (mat.m_rows[0][2] - mat.m_rows[2][0])/(2.0f*r);
        }
        else
        {
            r = std::sqrt(mat.m_rows[2][2] - (mat.m_rows[0][0] + mat.m_rows[1][1]) + 1);
            result.m_data[3] = r/2.0f;
            result.m_data[1] = (mat.m_rows[2][0] - mat.m_rows[0][2])/(2.0f*r);
            result.m_data[2] = (mat.m_rows[1][2] - mat.m_rows[2][1])/(2.0f*r);
            result.m_data[0]  = (mat.m_rows[1][0] - mat.m_rows[0][1])/(2.0f*r);
        }

        return result;
    }
}
