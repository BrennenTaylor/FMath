/**
 * @file Ray.h
 * @author Brennen Taylor (brtaylor1001@gmail.com)
 * @brief Declares the ray class
 * @version 0.1
 * @date 2019-03-12
 *
 * @copyright Copyright (c) 2019
 *
 */

#pragma once

#include "Vector3.h"

/**
 * @brief The farlor 3d graphics libraries
*/

namespace Farlor
{
    /**
     * @brief Class which represents a ray.
    */

    class Ray
    {
    public:

        /**
         * @brief Construct a new Ray object
         *
         * @param direction
         * @param origin
         */
        Ray(const Vector3& direction, const Vector3& origin) noexcept;

    public:
        Vector3 m_direction;
        float m_length;
        Vector3 m_origin;
    };
}
