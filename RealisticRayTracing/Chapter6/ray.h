// Ray.h
#pragma once

#include "vector3.h"

class Ray
{
public:
    Vector3 data[2];

    Ray() = default;
    
    Ray(const Vector3& pos, const Vector3& dir)
    {
        data[0] = pos; 
        data[1] = dir;
    }

    Ray(const Ray& value)
    { *this = value; }

    Vector3 origin() const
    { return data[0]; }

    Vector3 direction() const
    { return data[1]; }

    Vector3 pointAtParameter(float t) const
    { return data[0] + t * data[1]; }
};

inline std::ostream& operator << (std::ostream& os, const Ray& ray)
{
    os << "(" << ray.origin() << ") + t(" << ray.direction() << ")";
    return os;
}