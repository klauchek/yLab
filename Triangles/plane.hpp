#ifndef PLANE_H
#define PLANE_H

#include "vector.hpp"


class Plane {
private:
    //! Plane equation in form (r - r0, n) = 0 <=> (r, n) = (r0, n) = D
    //! Normal vector of the plane
    Vector norma;
    double D; //projection of radius-vector of any point thet belongs the plane on normal: INV!

public:

    //! Using plane equation in form (r - r0, r1 - r0, r2 - 0) = 0; D = (r0, n)
    Plane(const Vector& r0, const Vector& r1, const Vector& r2) : norma(VecProduct((r2 - r0), (r1 - r0)).normalize()),
                                                                    D(ScalarProduct(r0, norma))
    {}

    Plane(const Plane& plane) : norma(plane.norma),
                                D(plane.D)
    {}

    Plane() : norma(Vector()),
              D(0)
    {}

    //! Getters for class plane
    Vector getNorma()
    {
        return norma;
    }
    float getD()
    {
        return D;
    }

    //! Calculate distance from point(vector) to plane dist = (r, n) - (r0, n) = (r, n) - D

    bool DistToVec(const Vector& vector)
    {
        float dist = ScalarProduct(vector, norma) - D;
        if (dist < 0)
            return false;
        return true;
    }

};

#endif

