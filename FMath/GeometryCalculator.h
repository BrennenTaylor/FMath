/**
 * @file GeometryCalculator.h
 * @author Brennen Taylor (brtaylor1001@gmail.com)
 * @brief Contains free functions for geometric calculations.
 * @version 0.1
 * @date 2019-03-12
 *
 * @copyright Copyright (c) 2019
 *
 */

#pragma once

#include "FMath.h"
#include "Plane.h"

/**
 * @brief The farlor 3d graphics libraries
*/

namespace Farlor
{

    /**
     * @brief Collection of geometry based function operations
    */
    namespace GeometryCalculator
    {
        /**
         * @brief Calculates the barycentric coordinates of a point within
         * a given triangle made from three given vertices.
         *
         * @param v0 First vertex in triangle
         * @param v1 Second vertex in triangle
         * @param v2 Third vertex in triangle
         * @param point Point to check inside triangle
         * @return Vector3
         */
        Vector3 Barycentric(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 point);

        /**
         * @brief Checks if a point is within
         * a given triangle made from three given vertices.
         *
         * @param v0 First vertex in triangle
         * @param v1 Second vertex in triangle
         * @param v2 Third vertex in triangle
         * @param point Point to check inside triangle
         * @return bool
         */
        bool PointInTriangle(Vector3 v0, Vector3 v1, Vector3 v2, Point point);

        /**
         * @brief Creates a plane from a triangle from three
         * specified vertices.
         *
         * @param v0 First vertex in triangle
         * @param v1 Second vertex in triangle
         * @param v2 Third vertex in triangle
         * @return Plane
         */
        Plane GeneratePlaneCCW(Vector3 v0, Vector3 v1, Vector3 v2);

        /**
         * @brief Checks if a quad specified by four vertices is
         * convex.
         *
         * @param v0 First vertex in triangle
         * @param v1 Second vertex in triangle
         * @param v2 Third vertex in triangle
         * @param v3 Fourth vertex in triangle
         * @return bool
         */
        bool IsQuadConvex(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3);
    };
}