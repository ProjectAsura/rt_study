// UVSphere.h
#pragma once

#include "shape.h"
#include "ray.h"
#include "texture.h"


class UVSphere : public Shape
{
public:
    UVSphere(const Vector3& c, float r, Texture* tex);
    bool hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const override;
    bool shadowHit(const Ray& ray, float tmin, float tmax, float time) const override;

    Vector3  center;
    float    radius;
    Texture* texture;
};
