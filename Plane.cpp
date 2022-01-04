#include "FMath/Plane.h"

namespace Farlor
{
    Plane::Plane() noexcept
        : m_normal(0.0f, 0.0f, 0.0f)
        , m_offset(0.0f)
    {
    }
    Plane::Plane(float a, float b, float c, float d) noexcept
        : m_normal(a, b, c)
        , m_offset(d)
    {
    }
}