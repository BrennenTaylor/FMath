#include "FMath/Plane.h"

namespace Farlor
{
    Plane::Plane()
        : m_normal(0.0f, 0.0f, 0.0f)
        , m_offset(0.0f)
    {
    }
    Plane::Plane(float a, float b, float c, float d)
        : m_normal(a, b, c)
        , m_offset(d)
    {
    }
}