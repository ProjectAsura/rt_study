// Shape.h
#pragma once

#include "ray.h"
#include "vector3.h"
#include "rgb.h"

struct HitRecord
{
    float   t;
    Vector3 normal;
    rgb     color;
};

class Shape
{
public:
    virtual bool hit(const Ray& ray, float tmin, float max, float time, HitRecord& record) const = 0;
    virtual bool shadowHit(const Ray& ray, float tmin, float tmax, float time) const = 0;
};