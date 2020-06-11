#include "FMath/Matrix4x4.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/ext/matrix_transform.hpp>

#include <cmath>

namespace Farlor
{
    Matrix4x4 Matrix4x4::s_Identity = Matrix4x4(
        Vector4(1.0f, 0.0f, 0.0f, 0.0f),
        Vector4(0.0f, 1.0f, 0.0f, 0.0f),
        Vector4(0.0f, 0.0f, 1.0f, 0.0f),
        Vector4(0.0f, 0.0f, 0.0f, 1.0f));

    Matrix4x4::Matrix4x4()
    {
        m_rows[0] = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
        m_rows[1] = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
        m_rows[2] = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
        m_rows[3] = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
    }

    Matrix4x4::Matrix4x4(const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4)
    {
        m_rows[0] = row1;
        m_rows[1] = row2;
        m_rows[2] = row3;
        m_rows[3] = row4;
    }

    Matrix4x4::Matrix4x4(const Quaternion& q, const Vector3& pos)
    {
        m_r1c1 = 1 - 2 * q.m_data[2]*q.m_data[2] - 2 * q.m_data[3]*q.m_data[3];
        m_r1c2 = 2 * q.m_data[1]*q.m_data[2] - 2 * q.m_data[0]*q.m_data[3];
        m_r1c3 = 2 * q.m_data[1]*q.m_data[3] + 2 * q.m_data[0]*q.m_data[2];

        m_r2c1 = 2 * q.m_data[1]*q.m_data[2] + 2 * q.m_data[0]*q.m_data[3];
        m_r2c2 = 1 - 2 * q.m_data[1]*q.m_data[1] - 2 * q.m_data[3]*q.m_data[3];
        m_r2c3 = 2 * q.m_data[2]*q.m_data[3] - 2 * q.m_data[0]*q.m_data[1];

        m_r3c1 = 2 * q.m_data[1]*q.m_data[3] - 2 * q.m_data[0]*q.m_data[2];
        m_r3c2 = 2 * q.m_data[2]*q.m_data[3] + 2 * q.m_data[0]*q.m_data[1];
        m_r3c3 = 1 - 2 * q.m_data[1]*q.m_data[1] - 2 * q.m_data[2]*q.m_data[2];
        m_r1c4 = pos.x;
        m_r2c4 = pos.y;
        m_r3c4 = pos.z;

        m_rows[3] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4x4::Matrix4x4(float r1c1, float r1c2, float r1c3, float r1c4,
            float r2c1, float r2c2, float r2c3, float r2c4,
            float r3c1, float r3c2, float r3c3, float r3c4,
            float r4c1, float r4c2, float r4c3, float r4c4)
    {
        m_r1c1 = r1c1;
        m_r1c2 = r1c2;
        m_r1c3 = r1c3;
        m_r1c4 = r1c4;

        m_r2c1 = r2c1;
        m_r2c2 = r2c2;
        m_r2c3 = r2c3;
        m_r2c4 = r2c4;

        m_r3c1 = r3c1;
        m_r3c2 = r3c2;
        m_r3c3 = r3c3;
        m_r3c4 = r3c4;

        m_r4c1 = r4c1;
        m_r4c2 = r4c2;
        m_r4c3 = r4c3;
        m_r4c4 = r4c4;
    }

    Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& rhs)
    {
        m_rows[0] += rhs.m_rows[0];
        m_rows[1] += rhs.m_rows[1];
        m_rows[2] += rhs.m_rows[2];
        m_rows[3] += rhs.m_rows[3];
        return *this;
    }

    Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const
    {
        return Matrix4x4(*this) += other;
    }
    // Subtract
    Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& rhs)
    {
        m_rows[0] -= rhs.m_rows[0];
        m_rows[1] -= rhs.m_rows[1];
        m_rows[2] -= rhs.m_rows[2];
        m_rows[3] -= rhs.m_rows[3];
        return *this;
    }

    Matrix4x4 Matrix4x4::operator-(const Matrix4x4 &other) const
    {
        return Matrix4x4(*this) -= other;
    }

    Matrix4x4& Matrix4x4::Matrix4x4::operator*=(const Matrix4x4 &rhs)
    {
        Matrix4x4 result;
        // Fix matrix multipliaction
        for (uint32_t r = 0; r < 4; ++r)
        {
            for (uint32_t c = 0; c < 4; ++c)
            {
                float val = 0.0;
                for (uint32_t i = 0; i < 4; ++i)
                {
                    val += m_rows[r][i] * rhs.m_rows[i][c];
                }
                result.m_rows[r][c] = val;
            }
        }

        for (uint32_t i = 0; i < 4*4; ++i)
        {
            m_data[i] = result.m_data[i];
        }

        return *this;
    }
    Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &other) const
    {
        return Matrix4x4(*this) *= other;
    }

    // Use % as dot product
    // Matrix4x4& Matrix4x4::operator%=( Matrix4x4 &rhs) = delete;
    // float operator%( Matrix4x4 &vec);
    // Equality
    bool Matrix4x4::operator==(const Matrix4x4 &other) const
    {
        return (m_rows[0] == other.m_rows[0]) && (m_rows[1] == other.m_rows[1]) && (m_rows[2] == other.m_rows[2]) && (m_rows[3] == other.m_rows[3]);
    }
    bool Matrix4x4::operator!=(const Matrix4x4 &other) const
    {
        return !(*this == other);
    }

    // Vector & T
    // Multiply
    Matrix4x4& Matrix4x4::operator*=(const float rhs)
    {
        m_rows[0] *= rhs;
        m_rows[1] *= rhs;
        m_rows[2] *= rhs;
        m_rows[3] *= rhs;
        return (*this);
    }

    Matrix4x4 Matrix4x4::operator*(const float rhs) const
    {
        return Matrix4x4(*this) *= rhs;
    }

    Vector4 Matrix4x4::operator*(const Vector4 &rhs) const
    {
        Vector4 val;
        val.x = m_rows[0].Dot(rhs);
        val.y = m_rows[1].Dot(rhs);
        val.z = m_rows[2].Dot(rhs);
        val.w = m_rows[3].Dot(rhs);
        return val;
    }

    // Divide
    Matrix4x4& Matrix4x4::operator/=(const float rhs)
    {
        m_rows[0] /= rhs;
        m_rows[1] /= rhs;
        m_rows[2] /= rhs;
        m_rows[3] /= rhs;
        return (*this);
    }

    Matrix4x4 Matrix4x4::operator/(const float rhs) const
    {
        return Matrix4x4(*this) /= rhs;
    }

    // Standalone
    Matrix4x4 operator*(const float lhs, const Matrix4x4& rhs)
    {
        return Matrix4x4(lhs * rhs.m_rows[0], lhs * rhs.m_rows[1], lhs * rhs.m_rows[2], lhs * rhs.m_rows[3]);
    }

    // Out Streaming
    std::ostream& operator<<(std::ostream& os, const Matrix4x4& mat)
    {
        os << mat.m_rows[0] << mat.m_rows[1] << mat.m_rows[2] << mat.m_rows[3] << std::endl;
        return os;
    }

    Matrix4x4 Matrix4x4::Inversed() const
    {
        Matrix4x4 val(*this);

        glm::mat4 tempRotate;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                tempRotate[i][j] = val.m_rows[i][j];
            }
        }

        glm::mat4 inverseMat = inverse(tempRotate);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                val.m_rows[i][j] = inverseMat[i][j];
            }
        }

        return val;
    }

    Matrix4x4 Matrix4x4::Transposed() const
    {
        Matrix4x4 val(*this);

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

        temp = val.m_r1c4;
        val.m_r1c4 = val.m_r4c1;
        val.m_r4c1 = temp;

        temp = val.m_r2c4;
        val.m_r2c4 = val.m_r4c2;
        val.m_r4c2 = temp;

        temp = val.m_r3c4;
        val.m_r3c4 = val.m_r4c3;
        val.m_r4c3 = temp;

        return val;
    }

    Matrix4x4 Matrix4x4::InverseTransposed() const
    {
        Matrix4x4 val(*this);

        val = val.Inversed();

        std::cout << "Inversed: " << val << std::endl;

        val = val.Transposed();

        return val;
    }

    float Matrix4x4::Determinant() const
    {
        Matrix4x4 val(*this);

        glm::mat4 tempRotate;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                tempRotate[i][j] = val.m_rows[i][j];
            }
        }

        return glm::determinant(tempRotate);
    }

    Matrix4x4 Matrix4x4::TranslationMatrix(const Vector3& translation)
    {
        Matrix4x4 result;
        result.m_rows[0] = Vector4(1.0f, 0.0f, 0.0f, translation.x);
        result.m_rows[1] = Vector4(0.0f, 1.0f, 0.0f, translation.y);
        result.m_rows[2] = Vector4(0.0f, 0.0f, 1.0f, translation.z);
        result.m_rows[3] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
        return result;
    }

    Matrix4x4 Matrix4x4::RotationMatrix(const Quaternion& rotation)
    {
        Matrix4x4 result(rotation, Vector3(0.0f, 0.0f, 0.0f));
        return result;
    }

    Matrix4x4 Matrix4x4::RotationYawPitchRollMatrix(const Vector3& yawPitchRoll)
    {
        float yawCos = std::cos(yawPitchRoll.x);
        float yawSin = std::sin(yawPitchRoll.x);

        float pitchCos = std::cos(yawPitchRoll.y);
        float pitchSin = std::sin(yawPitchRoll.y);

        float rollCos = std::cos(yawPitchRoll.z);
        float rollSin = std::sin(yawPitchRoll.z);

        Matrix4x4 yawMatrix(
            Vector4(yawCos, -yawSin, 0.0f, 0.0f),
            Vector4(yawSin, yawCos, 0.0f, 0.0f),
            Vector4(0.0f, 0.0f, 1.0f, 0.0f),
            Vector4(0.0f, 0.0f, 0.0f, 1.0f)
        );

        Matrix4x4 pitchMatrix(
            Vector4(pitchCos, 0.0f, pitchSin, 0.0f),
            Vector4(0.0f, 1.0f, 0.0f, 0.0f),
            Vector4(-pitchSin, 0.0f, pitchCos, 0.0f),
            Vector4(0.0f, 0.0f, 0.0f, 1.0f)
        );

        Matrix4x4 rollMatrix(
            Vector4(1.0f, 0.0f, 0.0f, 0.0f),
            Vector4(0.0f, rollCos, -rollSin, 0.0f),
            Vector4(0.0f, rollSin, rollCos, 0.0f),
            Vector4(0.0f, 0.0f, 0.0f, 1.0f)
        );

        return rollMatrix * pitchMatrix * yawMatrix;
    }

    Matrix4x4 Matrix4x4::ScaleMatrix(const Vector3& scale)
    {
        Matrix4x4 result;
        result.m_rows[0] = Vector4(scale.x, 0.0f, 0.0f, 0.0f);
        result.m_rows[1] = Vector4(0.0f, scale.y, 0.0f, 0.0f);
        result.m_rows[2] = Vector4(0.0f, 0.0f, scale.z, 0.0f);
        result.m_rows[3] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
        return result;
    }

    Matrix4x4 Matrix4x4::LookAtLH(const Vector3& pos, const Vector3& target, const Vector3& worldUp)
    {
        glm::vec3 posFloat(pos.x, pos.y, pos.z);
        glm::vec3 targetFloat(target.x, target.y, target.z);
        glm::vec3 worldUpFloat(worldUp.x, worldUp.y, worldUp.z);

        glm::mat4 tempValue = glm::lookAtLH(posFloat, targetFloat, worldUpFloat);

        Matrix4x4 value;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                value.m_rows[i][j] = tempValue[i][j];
            }
        }
        // TODO: Why does this need to be Transposed?
        return value.Transposed();
    }

    // Expects radians
    Matrix4x4 Matrix4x4::PerspectiveLHFOV(float fov, float aspect, float zNear, float zFar)
    {

        glm::mat4 tempValue = glm::perspective(fov, aspect, zNear, zFar);
        Matrix4x4 value;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                value.m_rows[i][j] = tempValue[i][j];
            }
        }
        // TODO: Why does this need to be Transposed?
        return value.Transposed();
    }

    // Expects radians
    Matrix4x4 Matrix4x4::OrthographicPerspectiveLH(float viewWidth, float viewHeight, float zNear, float zFar)
    {
        // Expects radians
        glm::mat4 tempValue = glm::ortho(0.0f, viewWidth, viewHeight, 0.0f, zNear, zFar);
        Matrix4x4 value;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                value.m_rows[i][j] = tempValue[i][j];
            }
        }

        // TODO: Why does this need to be Transposed?
        return value.Transposed();
    }
}
