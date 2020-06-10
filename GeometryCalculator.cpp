#include "FMath/GeometryCalculator.h"

namespace Farlor
{
    Vector3 GeometryCalculator::Barycentric(Vector3 a, Vector3 b, Vector3 c, Vector3 p)
    {
        Vector3 ab = b-a;
        Vector3 ac = c-a;
        Vector3 ap = p-a;

        float dotABAB = ab.Dot(ab);
        float dotABAC = ab.Dot(ac);
        float dotACAC = ac.Dot(ac);
        float dotAPAB = ap.Dot(ab);
        float dotAPAC = ap.Dot(ac);

        float denom = dotABAB * dotACAC - dotABAC * dotABAC;

        Vector3 bary;
        bary.y = (dotACAC * dotAPAB - dotABAC * dotAPAC) / denom;
        bary.z = (dotABAB * dotAPAC - dotABAC * dotAPAB) / denom;
        bary.x = 1.0f - bary.y - bary.z;

        return bary;
    }

    bool GeometryCalculator::PointInTriangle(Vector3 a, Vector3 b, Vector3 c, Point p)
    {
        Vector3 bary = Barycentric(a, b, c, p);
        return bary.y >= 0.0f && bary.z >= 0.0 && (bary.y + bary.z) <= 1.0f;
    }

    Plane GeometryCalculator::GeneratePlaneCCW(Vector3 a, Vector3 b, Vector3 c)
    {
        Plane p;
        p.m_normal = ((b-a).Cross(c-a)).Normalized();
        p.m_offset = p.m_normal.Dot(a);

        return p;
    }

    bool GeometryCalculator::IsQuadConvex(Vector3 a, Vector3 b, Vector3 c, Vector3 d)
    {
        Vector3 bda = (d-b).Cross(a-b);
        Vector3 bdc = (d-b).Cross(c-b);
        if (bda.Dot(bdc) >= 0.0f)
        {
            return false;
        }

        Vector3 acd = (c-a).Cross(d-a);
        Vector3 acb = (c-a).Cross(b-a);
        return acd.Dot(acb) < 0.0f;
    }
}