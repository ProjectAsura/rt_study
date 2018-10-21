// Vector3.h
#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif//_USE_MATH_DEFINES

#include <cmath>
#include <iostream>

class Vector3
{
public:
    float e[3];

    Vector3() 
    { e[0] = e[1] = e[2] = 0.0f; }

    Vector3(float e0, float e1, float e2)
    { e[0] = e0; e[1] = e1; e[2] = e2; }

    Vector3(const Vector3& v) 
    { *this = v; }

    float x() const { return e[0]; }
    float y() const { return e[1]; }
    float z() const { return e[2]; }
    void setX(float _x) { e[0] = _x; }
    void setY(float _y) { e[1] = _y; }
    void setZ(float _z) { e[2] = _z; }

    Vector3 operator + () const { return *this; }
    Vector3 operator - () const { return Vector3(-e[0], -e[1], -e[2]); }

    float  operator[] (int i) const { return e[i]; }
    float& operator[] (int i)       { return e[i]; }

    float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
    float squaredLength() const { return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }

    void  makeUnitVector();

    float minComponent() const;
    float maxComponent() const;
    float minAbsComponent() const;
    float maxAbsComponent() const;
    int   indexOfMinComponent() const;
    int   indexOfMaxComponent() const;
    int   indexOfMinAbsComponent() const;
    int   indexOfMaxAbsComponent() const;

    Vector3& operator =  (const Vector3& value);
    Vector3& operator += (const Vector3& value);
    Vector3& operator -= (const Vector3& value);
    Vector3& operator *= (float value);
    Vector3& operator /= (float value);
};

inline void Vector3::makeUnitVector()
{
    auto mag = length();
    if (mag > 0)
    {
        e[0] /= mag;
        e[1] /= mag;
        e[2] /= mag;
    }
}

inline float Vector3::minComponent() const
{
    auto ret = e[0];
    if (e[1] < ret) ret = e[1];
    if (e[2] < ret) ret = e[2];
    return ret;
}

inline float Vector3::maxComponent() const
{
    auto ret = e[0];
    if (e[1] > ret) ret = e[1];
    if (e[2] > ret) ret = e[2];
    return ret;
}

inline float Vector3::minAbsComponent() const
{
    auto x = fabs(e[0]);
    auto y = fabs(e[1]);
    auto z = fabs(e[2]);
    auto ret = x;
    if (y < ret) ret = y;
    if (z < ret) ret = z;
    return ret;
}

inline float Vector3::maxAbsComponent() const
{
    auto x = fabs(e[0]);
    auto y = fabs(e[1]);
    auto z = fabs(e[2]);
    auto ret = x;
    if (y > ret) ret = y;
    if (z > ret) ret = z;
    return ret;
}

inline int Vector3::indexOfMinComponent() const
{
    auto index = 0;
    auto temp = e[0];
    if (e[1] < temp) { temp = e[1]; index = 1; }
    if (e[2] < temp) { index = 2; }

    return index;
}

inline int Vector3::indexOfMaxComponent() const
{
    auto index = 0;
    auto temp = e[0];
    if (e[1] > temp) { temp = e[1]; index = 1; }
    if (e[2] > temp) { index = 2; }

    return index;
}

inline int Vector3::indexOfMinAbsComponent() const
{
    auto x = fabs(e[0]);
    auto y = fabs(e[1]);
    auto z = fabs(e[2]);
    auto index = 0;
    auto temp = x;
    if (y < temp) { temp = y; index = 1; }
    if (z < temp) { index = 2; }
 
    return index;
}

inline int Vector3::indexOfMaxAbsComponent() const
{
    auto x = fabs(e[0]);
    auto y = fabs(e[1]);
    auto z = fabs(e[2]);
    auto index = 0;
    auto temp = x;
    if (y > temp) { temp = y; index = 1; }
    if (z > temp) { index = 2; }

    return index;
}

inline Vector3& Vector3::operator = (const Vector3& value)
{
    e[0] = value.e[0];
    e[1] = value.e[1];
    e[2] = value.e[2];
    return *this;
}

inline Vector3& Vector3::operator += (const Vector3& value)
{
    e[0] += value.e[0];
    e[1] += value.e[1];
    e[2] += value.e[2];
    return *this;
}

inline Vector3& Vector3::operator -= (const Vector3& value)
{
    e[0] -= value.e[0];
    e[1] -= value.e[1];
    e[2] -= value.e[2];
    return *this;
}

inline Vector3& Vector3::operator *= (float value)
{
    e[0] *= value;
    e[1] *= value;
    e[2] *= value;
    return *this;
}

inline Vector3& Vector3::operator /= (float value)
{
    e[0] /= value;
    e[1] /= value;
    e[2] /= value;
    return *this;
}

inline bool operator == (const Vector3& lhs, const Vector3& rhs)
{
    if (fabs(lhs.e[0] - rhs.e[0]) >= FLT_EPSILON) return false;
    if (fabs(lhs.e[1] - rhs.e[1]) >= FLT_EPSILON) return false;
    if (fabs(lhs.e[2] - rhs.e[2]) >= FLT_EPSILON) return false;
    return true;
}

inline std::istream& operator >> (std::istream& is, Vector3& value)
{
    is >> value.e[0] >> value.e[1] >> value.e[2];
    return is;
}

inline std::ostream& operator << (std::ostream& os, const Vector3& value)
{
    os << '(' << value.e[0] << " " << value.e[1] << " " << value.e[2] << ')';
    return os;
}

inline bool operator != (const Vector3& lhs, const Vector3& rhs)
{ return !(lhs == rhs); }

inline Vector3 operator + (const Vector3& lhs, const Vector3& rhs)
{ return Vector3(lhs.e[0] + rhs.e[0], lhs.e[1] + rhs.e[1], lhs.e[2] + rhs.e[2]); }

inline Vector3 operator - (const Vector3& lhs, const Vector3& rhs)
{ return Vector3(lhs.e[0] - rhs.e[0], lhs.e[1] - rhs.e[1], lhs.e[2] - rhs.e[2]); }

inline Vector3 operator / (const Vector3& lhs, float rhs)
{ return Vector3(lhs.e[0] / rhs, lhs.e[1] / rhs, lhs.e[2] / rhs); }

inline Vector3 operator * (float lhs, const Vector3& rhs)
{ return Vector3(lhs * rhs.e[0], lhs * rhs.e[1], lhs * rhs.e[2]); }

inline Vector3 operator * (const Vector3& lhs, float rhs)
{ return Vector3(lhs.e[0] * rhs, lhs.e[1] * rhs, lhs.e[2] * rhs); }

inline Vector3 unitVector(const Vector3& value)
{
    auto mag = value.length();
    return (mag > 0) ? value / mag : value;
}

inline Vector3 minVec(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 result;
    result.e[0] = (lhs.e[0] < rhs.e[0]) ? lhs.e[0] : rhs.e[0];
    result.e[1] = (lhs.e[1] < rhs.e[1]) ? lhs.e[1] : rhs.e[1];
    result.e[2] = (lhs.e[2] < rhs.e[2]) ? lhs.e[2] : rhs.e[2];
    return result;
}

inline Vector3 maxVec(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 result;
    result.e[0] = (lhs.e[0] > rhs.e[0]) ? lhs.e[0] : rhs.e[0];
    result.e[1] = (lhs.e[1] > rhs.e[1]) ? lhs.e[1] : rhs.e[1];
    result.e[2] = (lhs.e[2] > rhs.e[2]) ? lhs.e[2] : rhs.e[2];
    return result;
}

inline Vector3 cross(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 result;
    result.e[0] = lhs.y() * rhs.z() - lhs.z() * rhs.y();
    result.e[1] = lhs.z() * rhs.x() - lhs.x() * rhs.z();
    result.e[2] = lhs.x() * rhs.y() - lhs.y() * rhs.x();
    return result;
}

inline float dot(const Vector3& lhs, const Vector3& rhs)
{ return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z(); }

inline float tripleProduct(const Vector3& v1, const Vector3& v2, const Vector3& v3)
{ return dot(cross(v1, v2), v3); }

