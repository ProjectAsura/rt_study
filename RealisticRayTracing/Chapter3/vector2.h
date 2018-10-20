// Vector2.h
#pragma once

#include <cmath>
#include <iostream>


class Vector2
{
public:
    float e[2];

    Vector2() { e[0] = e[1] = 0.0f; }
    Vector2(float e0, float e1) { e[0] = e0; e[1] = e1; }
    Vector2(const Vector2& value) { e[0] = value.e[0]; e[1] = value.e[1]; }

    float x() const { return e[0]; }
    float y() const { return e[1]; }
    void setX(float value) { e[0] = value; }
    void setY(float value) { e[1] = value; }

    Vector2 operator + () const { return *this; }
    Vector2 operator - () const { return Vector2(-e[0], -e[1]); }

    float& operator[](int i)       { return e[i]; }
    float  operator[](int i) const { return e[i]; }

    float length() const { return sqrt(e[0] * e[0] + e[1] * e[1]); }
    float squaredLength() const { return e[0] * e[0] + e[1] * e[1]; }

    void makeUnitVector();

    Vector2& operator += (const Vector2& v) { e[0] += v.e[0]; e[1] += v.e[1]; return *this; }
    Vector2& operator -= (const Vector2& v) { e[0] -= v.e[0]; e[1] -= v.e[1]; return *this; }
    Vector2& operator *= (float t) { e[0] *= t; e[1] *= t; return *this; }
    Vector2& operator /= (float t) { e[0] /= t; e[1] /= t; return *this; }
};

inline void Vector2::makeUnitVector()
{
    auto mag = length();
    if (mag > 0)
    {
        e[0] /= mag;
        e[1] /= mag;
    }
}

inline bool operator == (const Vector2& lhs, const Vector2& rhs)
{
    if (fabs(lhs.e[0] - rhs.e[0]) >= FLT_EPSILON) return false;
    if (fabs(lhs.e[1] - rhs.e[1]) >= FLT_EPSILON) return false;
    return true;
}

inline bool operator != (const Vector2& lhs, const Vector2& rhs)
{ return !(lhs == rhs); }

inline std::istream& operator >> (std::istream& is, Vector2& value)
{
    is >> value.e[0] >> value.e[1];
    return is;
}

inline std::ostream& operator << (std::ostream& os, const Vector2& value)
{
    os << '(' << value.e[0] << " " << value.e[1] << ')';
    return os;
}

inline Vector2 operator + (const Vector2& lhs, const Vector2& rhs)
{ return Vector2(lhs.e[0] + rhs.e[0], lhs.e[1] + rhs.e[1]); }

inline Vector2 operator - (const Vector2& lhs, const Vector2& rhs)
{ return Vector2(lhs.e[0] - rhs.e[0], lhs.e[1] - rhs.e[1]); }

inline Vector2 operator * (float lhs, const Vector2& rhs)
{ return Vector2(lhs * rhs.e[0], lhs * rhs.e[1]); }

inline Vector2 operator * (const Vector2& lhs, float rhs)
{ return Vector2(lhs.e[0] * rhs, lhs.e[1] * rhs); }

inline Vector2 operator / (const Vector2& lhs, float rhs)
{ return Vector2(lhs.e[0] / rhs, lhs.e[1] / rhs); }

inline float dot(const Vector2& lhs, const Vector2& rhs)
{ return lhs.e[0] * rhs.e[0] + lhs.e[1] * rhs.e[1]; }

inline Vector2 unitVector(const Vector2& value)
{
    auto mag = value.length();
    return (mag > 0) ? value / mag : value;
}
