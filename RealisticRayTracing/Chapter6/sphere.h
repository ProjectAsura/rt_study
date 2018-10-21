﻿// Sphere.h
#pragma once

#include "shape.h"
#include "vector3.h"
#include "ray.h"
#include "simple_texture.h"


class Sphere : public Shape
{
public:
    Vector3 center;
    float   radius;
    SimpleTexture texture;

    Sphere(const Vector3& pos, float r, const rgb& col);
    bool hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const override;
    bool shadowHit(const Ray& ray, float tmin, float tmax, float time) const override;
};
