#ifndef __PVector__
#define __PVector__

#include "Header.hpp"

struct PVector
{
    double x, y;

    //* Constructors *//
    PVector()
    {
        x = 0;
        y = 0;
    }
    PVector(double _x, double _y)
    {
        x = _x;
        y = _y;
    }
    //* Destructor *//
    ~PVector() {}

    //* Operators *//
    // Substitute PVector
    PVector operator=(const PVector &v)
    {
        x = v.x;
        y = v.y;
        return *this;
    }
    // Whether or not this vector is another vector
    bool operator==(const PVector &v)
    {
        return (x == v.x && y == v.y);
    }
    bool operator!=(const PVector &v)
    {
        return (x != v.x || y != v.y);
    }
    // / +=
    PVector operator+=(const PVector &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }
    // / -=
    PVector operator-=(const PVector &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    // / *=
    PVector operator*=(const double &a)
    {
        x *= a;
        y *= a;
        return *this;
    }
    // / /=
    PVector operator/=(const double &a)
    {
        x /= a;
        y /= a;
        return *this;
    }
    
    //* Methods *//
    double Dot(const PVector &v);
    double Norm();
    // double Dist(const PVector &v);
    double DistTroid(const PVector &v);
    PVector TroidalShortest(const PVector &v, const double &w, const double &h);
    void Normalize();
    void Rotate(const double &theta);
    double CalcBetweenAngle(const PVector &v);
};

PVector operator+(const PVector &v1, const PVector &v2);
PVector operator-(const PVector &v1, const PVector &v2);
PVector operator*(const double &a, const PVector &v);
PVector operator/(const PVector &v, const double &a);

double CalcBetweenAbsoluteAngle(const PVector &v1, const PVector &v2);

#endif