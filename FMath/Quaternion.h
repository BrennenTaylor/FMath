#pragma once

#include "Vector3.h"
#include "Vector4.h"

#include <iostream>

/**
 * @brief The farlor 3d graphics libraries
*/
namespace Farlor
{
    /**
     * @brief Class which represents a quaternion rotation
     *
     */
    class Quaternion
    {
    public:
        union
        {
            float m_data[4];
        };

        Quaternion();
        Quaternion(float newS, Vector3 newU);

        // Quaternion & Quaternion
        // Add
        Quaternion& operator+=(Quaternion &rhs);
        Quaternion operator+(Quaternion &vec);
        // Subtract
        Quaternion& operator-=(Quaternion &rhs);
        Quaternion operator-(Quaternion &vec);
        // Multiply
        Quaternion& operator*=(Quaternion &rhs);
        Quaternion operator*(Quaternion &vec);
        // Divide
        Quaternion& operator/=(Quaternion &rhs);
        Quaternion operator/(Quaternion &vec);
        // Use % as dot product
        Quaternion& operator%=(Quaternion &rhs) = delete;
        float operator%(Quaternion &vec);
        // Equality
        bool operator==(Quaternion &other);
        bool operator!=(Quaternion &other);

        // Vector & T
        // Multiply
        Quaternion& operator*=(float &rhs);
        Quaternion operator*(float &rhs);
        // Divide
        Quaternion& operator/=(float &rhs);
        Quaternion operator/(float &rhs);

        // Standalone
        friend Quaternion operator*(float lhs, Quaternion& rhs);

        // Out Streaming
        friend std::ostream& operator<<(std::ostream& os, Quaternion& vec);

        // Local Math Operations
        float Magnitude();
        float SqrMagnitude();
        Quaternion Normalized();
        void Normalize();

        void RotateByVector(Vector3& vec);
        void AddScaledVector(Vector3& vec, float scale);

        static Quaternion RotationYawPitchRoll(float x, float y, float z);
        static Quaternion RotationAroundAxis(float angle, Vector3 axis);
    };
}
