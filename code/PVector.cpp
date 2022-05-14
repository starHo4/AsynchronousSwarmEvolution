#include "PVector.hpp"

//* Operator Overload
PVector operator+(const PVector &v1, const PVector &v2)
{
    double _x = v1.x + v2.x;
    double _y = v1.y + v2.y;
    return PVector(_x, _y);
}

PVector operator-(const PVector &v1, const PVector &v2)
{
    double _x = v1.x - v2.x;
    double _y = v1.y - v2.y;
    return PVector(_x, _y);
}

PVector operator*(const double &a, const PVector &v)
{
    double _x = v.x * a;
    double _y = v.y * a;
    return PVector(_x, _y);
}

PVector operator/(const PVector &v, const double &a)
{
    double _x = v.x / a;
    double _y = v.y / a;
    return PVector(_x, _y);
}

//* Methods *//

double PVector::Dot(const PVector &v)
{
    double a = x * v.x + y * v.y;
    return a;
}

double PVector::Norm()
{
    return sqrt(this->Dot(*this));
}

double PVector::DistTroid(const PVector &v)
{
    PVector tmp = TroidalShortest(v, FIELD_W, FIELD_H);
    return tmp.Norm();
}

PVector PVector::TroidalShortest(const PVector &v, const double &w, const double &h)
{
    if (abs(x) > w / 2 || abs(y) > h / 2)
    {
        cout << "Missing wrapped the environment." << endl;
        abort();
    }

    double dx = x - v.x;
    double dy = y - v.y;
    if (abs(dx) > w / 2)
    {
        dx = (x - w) - v.x;
    }
    if (abs(dy) > h / 2)
    {
        dy = (y - h) - v.y;
    }
    return PVector(dx, dy);
}

void PVector::Normalize()
{
    double norm = this->Norm();
    if (norm > 0)
    {
        x = x / norm;
        y = y / norm;
    }
}

void PVector::Rotate(const double &theta)
{
    double _x = x;
    double _y = y;
    x = _x * cos(theta) - _y * sin(theta);
    y = _x * sin(theta) + _y * cos(theta);
}

double PVector::CalcBetweenAngle(const PVector &v)
{
    return atan2(v.y, v.x) - atan2(y, x);
}

double CalcBetweenAbsoluteAngle(const PVector &v1, const PVector &v2)
{
    PVector v1_tmp = v1;
    PVector v2_tmp = v2;

    v1_tmp.Normalize();
    v2_tmp.Normalize();

    return acos(v1_tmp.Dot(v2_tmp));
}