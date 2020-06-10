#include "FMath/Ray.h"

namespace Farlor
{
    Ray::Ray(const Vector3& direction, const Vector3& origin)
        : m_direction(direction)
        , m_length(0.0f)
        , m_origin(origin)
    {
    }
}
