#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "vector.hpp"
#include "plane.hpp"
#include "triangle.hpp"

bool CompareSignDist(Plane& plane, Vector* points)
{
    int temp[3]{};
    int sum = 0;
    for (int i = 0; i < 3; ++i)
    {
        if (plane.DistToVec(points[i]) > 0)
            temp[i] = 1;
            ++sum;
    }
    if (sum % 3 != 0)
        return false;
    return true;
}


bool Intersection(const Triangle& triangle0, const Triangle& triangle1)
{
    Vector points0[3] = {triangle0.getVertex(0), triangle0.getVertex(1), triangle0.getVertex(2)};
    Vector points1[3] = {triangle1.getVertex(0), triangle1.getVertex(1), triangle1.getVertex(2)};

    Plane plane0(points0[0], points0[1], points0[2]);
    Vector n0 = plane0.getNorma();





    //MakeProjections();
    //CalcParams();
    //CompareSignDist();
    //

    //рассчитать через плоскости
    //Line inter_line;

    //float projections0[3];
    //float projections1[3];


}







/*
void Projections()
{
    for (int i = 0; i < 3; ++i)
        projections[i] = ScalarProduct()
}

*/



#endif