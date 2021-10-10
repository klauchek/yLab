#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

#define epsilon 0.00001

class Vector
{
private:
    float coord_[3];

public:

    Vector(float x, float y, float z) : coord_{x, y, z}
    {}

    Vector() : Vector(0, 0, 0)
    {}
//конструктор копирования!

    float getCoord(int axis) const
    {
        return coord_[axis];
    }

    void setCoord(float coord, int axis)
    {
        coord_[axis] = coord;
    }


//---------OVERLOADED OPERATORS----------------


    Vector operator+(const Vector& vector) const
    {
        return Vector(coord_[0] + vector.getCoord(0),
                        coord_[1] + vector.getCoord(1),
                        coord_[2] + vector.getCoord(2));
    }

    Vector operator-(const Vector& vector) const
    {
        return Vector(coord_[0] - vector.getCoord(0),
                        coord_[1] - vector.getCoord(1),
                        coord_[2] - vector.getCoord(2));
    }

    Vector operator -()
    {
        return Vector(-coord_[0], -coord_[1], -coord_[2]);
    }

    Vector operator /(const float value)
    {
        return Vector(coord_[0] / value,
                        coord_[1]/ value,
                        coord_[2] / value);
    }

    Vector operator*(const double value)
    {
        return Vector(value * coord_[0],
                        value * coord_[1],
                        value * coord_[2]);
    }

    bool operator ==(const Vector& vector) const
    {
        for (int i = 0; i < 3; ++i)
        {
            if (std::fabs(vector.coord_[i] - coord_[i]) > epsilon)
                return false;
        }
        return true;
    }

    Vector& operator ==(const Vector& vector)
    {
        for(int i = 0; i < 3; ++i)
                coord_[i] = vector.getCoord(i);
            return *this;
    }

    Vector& operator +=(const Vector& vector)
    {
        for(int i = 0; i < 3; ++i)
                coord_[i] += vector.getCoord(i);
            return *this;
    }

    Vector& operator -=(const Vector& vector)
    {
        for(int i = 0; i < 3; ++i)
                coord_[i] = vector.getCoord(i);
            return *this;
    }

    Vector& operator *=(const Vector& vector)
    {
        for(int i = 0; i < 3; ++i)
                coord_[i] *= vector.getCoord(i);
            return *this;
    }

    Vector& operator /=(const Vector& vector)
    {
        for(int i = 0; i < 3; ++i)
                coord_[i] /= vector.getCoord(i);
            return *this;
    }

};

/*Vector operator*(const double value, const Vector& vector)
{   
    return vector * value;
}
*/

std::istream& operator>>(std::istream &in, Vector &vector)
{
    float coord;
    for (int i = 0; i < 3; ++i)
    {
        in >> coord;
        vector.setCoord(coord, i);
    };
    return in;
}

std::ostream& operator<<(std::ostream& os, const Vector& vector)
{
    os << "(" << vector.getCoord(0) << "; "
                << vector.getCoord(1) << "; "
                << vector.getCoord(2) << ")";
    return os;
}

#endif