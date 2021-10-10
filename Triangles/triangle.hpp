#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>


class Triangle
{
private:
     Vector vecs_[3]{};

public:

    Triangle(const Vector& vec1, const Vector& vec2, const Vector& vec3) : vecs_{vec1, vec2, vec3}
    {}

    Triangle(): vecs_{}
    {}

    Triangle(const Triangle& trian)
    {
        for (int i = 0; i < 3; ++i)
        {
            vecs_[i] = trian.vecs_[i];
        }
    }

    Vector getVertex(int index) const
    {
        return vecs_[index];
    }

    void setVertex(Vector vector, int index)
    {
        vecs_[index] = vector;
    }

    //is valid??
};

    std::istream &operator>>(std::istream &in, Triangle &triangle)
    {
        Vector vecs_[3]{};

        in >> vecs_[0]>> vecs_[1] >> vecs_[2];

        for (int i = 0; i < 3; ++i)
            triangle.setVertex(vecs_[i], i);

        return in;
    }

    std::ostream& operator<<(std::ostream& os, const Triangle& triangle)
{
    os << "(" << triangle.getVertex(0) << "; "
                << triangle.getVertex(1) << "; "
                << triangle.getVertex(2) << ")";
    return os;
}


#endif