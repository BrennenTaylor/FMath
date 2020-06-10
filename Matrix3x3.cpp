#include "FMath/Matrix3x3.h"

#include <DirectXMath.h>

using namespace DirectX;
using namespace std;

namespace Farlor
{
    Matrix3x3 Matrix3x3::s_Identity = Matrix3x3(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));

    Matrix3x3::Matrix3x3()
    {
        m_rows[0] = Vector3(0.0f, 0.0f, 0.0f);
        m_rows[1] = Vector3(0.0f, 0.0f, 0.0f);
        m_rows[2] = Vector3(0.0f, 0.0f, 0.0f);
    }

    Matrix3x3::Matrix3x3(Vector3 row1, Vector3 row2, Vector3 row3)
    {
        m_rows[0] = row1;
        m_rows[1] = row2;
        m_rows[2] = row3;
    }

    Matrix3x3::Matrix3x3(Quaternion q)
    {
        m_r1c1 = 1 - 2*q.u.y*q.u.y - 2*q.u.z*q.u.z;
        m_r1c2 = 2*q.u.x*q.u.y - 2*q.s*q.u.z;
        m_r1c3 = 2*q.u.x*q.u.z + 2*q.s*q.u.y;

        m_r2c1 = 2*q.u.x*q.u.y + 2*q.s*q.u.z;
        m_r2c2 = 1 - 2*q.u.x*q.u.x - 2*q.u.z*q.u.z;
        m_r2c3 = 2*q.u.y*q.u.z - 2*q.s*q.u.x;

        m_r3c1 = 2*q.u.x*q.u.z - 2*q.s*q.u.y;
        m_r3c2 = 2*q.u.y*q.u.z + 2*q.s*q.u.x;
        m_r3c3 = 1 - 2*q.u.x*q.u.x - 2*q.u.y*q.u.y;
    }

    // Matrix3x3 & Matrix3x3
    // Add
    Matrix3x3& Matrix3x3::operator+=(const Matrix3x3 &rhs)
    {
        m_rows[0] += rhs.m_rows[0];
        m_rows[1] += rhs.m_rows[1];
        m_rows[2] += rhs.m_rows[2];
        return *this;
    }
    Matrix3x3 Matrix3x3::operator+(const Matrix3x3 &other) const
    {
        return Matrix3x3(*this) += other;
    }
    // Subtract
    Matrix3x3& Matrix3x3::operator-=(const Matrix3x3 &rhs)
    {
        m_rows[0] -= rhs.m_rows[0];
        m_rows[1] -= rhs.m_rows[1];
        m_rows[2] -= rhs.m_rows[2];
        return *this;
    }
    Matrix3x3 Matrix3x3::operator-(const Matrix3x3 &other) const
    {
        return Matrix3x3(*this) -= other;
    }
    // Multiply
    // r1c1 r1c2 r1c3
    // r2c1 r2c2 r2c3
    // r3c1 r3c2 r3c3
    Matrix3x3& Matrix3x3::Matrix3x3::operator*=(const Matrix3x3 &rhs)
    {
        Vector3 newRow0;
        Vector3 newRow1;
        Vector3 newRow2;

        newRow0.x = m_r1c1 * rhs.m_r1c1 + m_r1c2 * rhs.m_r2c1 + m_r1c3 * rhs.m_r3c1;
        newRow0.y = m_r1c1 * rhs.m_r1c2 + m_r1c2 * rhs.m_r2c2 + m_r1c3 * rhs.m_r3c2;
        newRow0.z = m_r1c1 * rhs.m_r1c3 + m_r1c2 * rhs.m_r2c3 + m_r1c3 * rhs.m_r3c3;

        newRow1.x = m_r2c1 * rhs.m_r1c1 + m_r2c2 * rhs.m_r2c1 + m_r2c3 * rhs.m_r3c1;
        newRow1.y = m_r2c1 * rhs.m_r1c2 + m_r2c2 * rhs.m_r2c2 + m_r2c3 * rhs.m_r3c2;
        newRow1.z = m_r2c1 * rhs.m_r1c3 + m_r2c2 * rhs.m_r2c3 + m_r2c3 * rhs.m_r3c3;

        newRow2.x = m_r3c1 * rhs.m_r1c1 + m_r3c2 * rhs.m_r2c1 + m_r3c3 * rhs.m_r3c1;
        newRow2.y = m_r3c1 * rhs.m_r1c2 + m_r3c2 * rhs.m_r2c2 + m_r3c3 * rhs.m_r3c2;
        newRow2.z = m_r3c1 * rhs.m_r1c3 + m_r3c2 * rhs.m_r2c3 + m_r3c3 * rhs.m_r3c3;

        m_rows[0] = newRow0;
        m_rows[1] = newRow1;
        m_rows[2] = newRow2;

        return *this;
    }
    Matrix3x3 Matrix3x3::operator*(const Matrix3x3 &other) const
    {
        return Matrix3x3(*this) *= other;
    }

    // // Divide
    // Matrix3x3& Matrix3x3::operator/=( Matrix3x3 &rhs)
    // {
    //
    // }
    //  Matrix3x3 operator/( Matrix3x3 &vec)
    //  {
    //
    //  }
    // Use % as dot product
    // Matrix3x3& Matrix3x3::operator%=( Matrix3x3 &rhs) = delete;
    // float operator%( Matrix3x3 &vec);
    // Equality
    bool Matrix3x3::operator==(const Matrix3x3 &other) const
    {
        return (m_rows[0] == other.m_rows[0]) && (m_rows[1] == other.m_rows[1]) && (m_rows[2] == other.m_rows[2]);
    }
    bool Matrix3x3::operator!=(const Matrix3x3 &other) const
    {
        return !(*this == other);
    }

    // Vector & T
    // Multiply
    Matrix3x3& Matrix3x3::operator*=( float &rhs)
    {
        m_rows[0] *= rhs;
        m_rows[1] *= rhs;
        m_rows[2] *= rhs;
        return (*this);
    }
    Matrix3x3 Matrix3x3::operator*( float &rhs) const
    {
        return Matrix3x3(*this) *= rhs;
    }

    Vector3 Matrix3x3::operator*(const Vector3 &rhs) const
    {
        Vector3 val;
        val.x = m_rows[0].Dot(rhs);
        val.y = m_rows[1].Dot(rhs);
        val.z = m_rows[2].Dot(rhs);
        return val;
    }

    // Divide
    Matrix3x3& Matrix3x3::operator/=( float &rhs)
    {
        m_rows[0] /= rhs;
        m_rows[1] /= rhs;
        m_rows[2] /= rhs;
        return (*this);
    }
    Matrix3x3 Matrix3x3::operator/( float &rhs) const
    {
        return Matrix3x3(*this) /= rhs;
    }

    // Standalone
    Matrix3x3 operator*(float lhs, const Matrix3x3& rhs)
    {
        return Matrix3x3(lhs * rhs.m_rows[0], lhs * rhs.m_rows[1], lhs * rhs.m_rows[2]);
    }

    // Out Streaming
    ostream& operator<<(ostream& os, Matrix3x3& mat)
    {
        os << mat.m_rows[0] << mat.m_rows[1] << mat.m_rows[2];
        return os;
    }

    Matrix3x3 Matrix3x3::Inversed() const
    {
        Matrix3x3 val(*this);

        XMFLOAT3X3 tempRotate;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                tempRotate.m[i][j] = val.m_rows[i][j];
            }
        }

        XMMATRIX matrixToInverse = XMLoadFloat3x3(&tempRotate);

        XMMATRIX inverse = XMMatrixInverse(nullptr, matrixToInverse);

        XMStoreFloat3x3(&tempRotate, inverse);

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                val.m_rows[i][j] = tempRotate.m[i][j];
            }
        }

        return val;
    }

    Matrix3x3 Matrix3x3::Transposed() const
    {
        Matrix3x3 val(*this);

        float temp;
        temp = val.m_r1c2;
        val.m_r1c2 = val.m_r2c1;
        val.m_r2c1 = temp;

        temp = val.m_r1c3;
        val.m_r1c3 = val.m_r3c1;
        val.m_r3c1 = temp;

        temp = val.m_r2c3;
        val.m_r2c3 = val.m_r3c2;
        val.m_r3c2 = temp;

        return val;
    }

    Quaternion Matrix3x3::ConvertToQuaternion(Matrix3x3& mat)
    {
        Quaternion result;

        float r;
        float t = mat.m_rows[0][0] + mat.m_rows[1][1] + mat.m_rows[2][2];

        if (t >= 0.0f)
        {
            r = std::sqrt(t+1);
            result.s = r/2.0f;
            result.u.x = (mat.m_rows[2][1] - mat.m_rows[1][2])/(2.0f*r);
            result.u.y = (mat.m_rows[0][2] - mat.m_rows[2][0])/(2.0f*r);
            result.u.z = (mat.m_rows[1][0] - mat.m_rows[0][1])/(2.0f*r);
        }
        else if (mat.m_rows[0][0] > mat.m_rows[1][1] && mat.m_rows[0][0] > mat.m_rows[2][2])
        {
            r = std::sqrt(mat.m_rows[0][0] - (mat.m_rows[1][1] + mat.m_rows[2][2]) + 1);
            result.u.x = r/2.0f;
            result.u.y = (mat.m_rows[0][1] - mat.m_rows[1][0])/(2.0f*r);
            result.u.z = (mat.m_rows[2][0] - mat.m_rows[0][2])/(2.0f*r);
            result.s = (mat.m_rows[2][1] - mat.m_rows[1][2])/(2.0f*r);
        }
        else if (mat.m_rows[1][1] > mat.m_rows[0][0] && mat.m_rows[1][1] > mat.m_rows[2][2])
        {
            r = std::sqrt(mat.m_rows[1][1] - (mat.m_rows[2][2] + mat.m_rows[0][0]) + 1);
            result.u.y = r/2.0f;
            result.u.z = (mat.m_rows[1][2] - mat.m_rows[2][1])/(2.0f*r);
            result.u.x = (mat.m_rows[0][1] - mat.m_rows[1][0])/(2.0f*r);
            result.s = (mat.m_rows[0][2] - mat.m_rows[2][0])/(2.0f*r);
        }
        else
        {
            r = std::sqrt(mat.m_rows[2][2] - (mat.m_rows[0][0] + mat.m_rows[1][1]) + 1);
            result.u.z = r/2.0f;
            result.u.x = (mat.m_rows[2][0] - mat.m_rows[0][2])/(2.0f*r);
            result.u.y = (mat.m_rows[1][2] - mat.m_rows[2][1])/(2.0f*r);
            result.s = (mat.m_rows[1][0] - mat.m_rows[0][1])/(2.0f*r);
        }

        return result;
    }
}
