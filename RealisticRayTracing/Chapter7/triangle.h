// Triangle.h
#pragma once

#include "shape.h"
#include "vector3.h"
#include "simple_texture.h"
#include "ray.h"


class Triangle : public Shape
{
public:
    Vector3 p0;
    Vector3 p1;
    Vector3 p2;
    SimpleTexture texture;

    Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, const rgb& col);
    bool hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const override;
    bool shadowHit(const Ray& ray, float tmin, float tmax, float time) const override;
};
