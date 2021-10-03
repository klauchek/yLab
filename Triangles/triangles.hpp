
#ifndef TRIANGLES_H
#define TRIANGLES_H

#include <iostream>


class Vector
{
private:
    float x_, y_, z_;

public:

    Vector(float x, float y, float z) : x_(x), y_(y), z_(z)
    {}

    Vector() : Vector(0, 0, 0)
    {}


    float getX() const
    {
        return x_;
    }
    float getY() const
    {
        return y_;
    }
    float getZ() const
    {
        return z_;
    }


    void setX(float x)
    {
         x_ = x;
    }
    void setY(float y)
    {
        y_ = y;
    }
    void setZ(float z)
    {
        z_ = z;
    }

\
    bool operator== (const Vector& vector) const
    {
        return x_ == vector.x_ && y_ == vector.y_ && z_ == vector.z_;
    }

    Vector operator+ (const Vector& vector) const
    {
        return Vector(x_ + vector.x_, y_ + vector.y_, z_ + vector.z_);
    }

    Vector operator *(const float value)
    {
        return Vector(value * x_, value * y_, value * z_);
    }T
};

std::istream& operator>>(std::istream &in, Vector &vector)
{
    float x, y, z;
    in >> x >> y >> z;
    vector.setX(x);
    vector.setY(y);
    vector.setZ(z);
    return in;
}

std::ostream& operator<<(std::ostream& os, const Vector& vector) {
    os << "(" << vector.getX() << "; " << vector.getY() << "; " << vector.getZ() << ")";
    return os;
}



//---------------------------------------------------------

class Triangle
{
private:
     Vector vec1_, vec2_, vec3_;

public:

    Triangle(const Vector& vec1, const Vector& vec2, const Vector& vec3) : vec1_(vec1), vec2_(vec2), vec3_(vec3)
    {}

    Triangle(): vec1_(0, 0, 0), vec2_(0, 0, 0), vec3_(0, 0, 0)
    {}


};

#endif