/**
 * @file Plane.h
 * @author Brennen Taylor (brtaylor1001@gmail.com   )
 * @brief Contains plane class, represented by a normal and
 * offset from that normal.
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
     * @brief Class which represents a geometric plane with
     * a normal and offset.
     *
     */
    class Plane
    {
    public:
        /**
         * @brief Construct a new Plane object
         *
         */
        Plane();
        /**
         * @brief Construct a new Plane object
         *
         * @param a
         * @param b
         * @param c
         * @param d
         */
        Plane(float a, float b, float c, float d);

    public:
        Vector3 m_normal;
        float m_offset;
    };
}