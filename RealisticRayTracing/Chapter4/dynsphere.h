// DynSphere.h
#pragma once

#include "shape.h"
#include "vector3.h"
#include "ray.h"
#include "rgb.h"


class DynSphere : public Shape
{
public:
    Vector3 center;
    float   min_time;
    float   max_time;
    float   radius;
    rgb     color;

    DynSphere(const Vector3& pos, float r, const rgb& col, float min_time, float max_time);

    bool hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const override;
    bool shadowHit(const Ray& ray, float tmin, float tmax, float time) const override;
    Vector3 getCenter(float time) const;
};