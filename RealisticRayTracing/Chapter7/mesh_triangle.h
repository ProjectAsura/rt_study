// MeshTriangle.h
#pragma once

#include "shape.h"

class Mesh;
class Texture;

class MeshTriangleUV : public Shape
{
public:
    MeshTriangleUV() = default;
    ~MeshTriangleUV() = default;
    MeshTriangleUV(Mesh* mesh, int p0, int p1, int p2);

    bool hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const override;
    bool shadowHit(const Ray& ray, float tmin, float tmax, float time) const override;

    // data members
    int     p[3];
    Mesh*   mesh_ptr;
};