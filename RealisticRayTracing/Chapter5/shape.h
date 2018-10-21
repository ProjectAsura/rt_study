// Shape.h
#pragma once

#include "ray.h"
#include "vector2.h"
#include "vector3.h"
#include "texture.h"


struct HitRecord
{
    float           t;
    Vector3         normal;
    Vector2         uv;
    Vector3         hit_p;
    const Texture*  hit_tex;
};

class Shape
{
public:
    virtual bool hit(const Ray& ray, float tmin, float max, float time, HitRecord& record) const = 0;
    virtual bool shadowHit(const Ray& ray, float tmin, float tmax, float time) const = 0;
};