// Mesh.h
#pragma once

#include "vertex.h"
#include "shape.h"
#include "texture.h"

class Mesh
{
public:
    Mesh() = default;
    ~Mesh() = default;

    Texture* getTexture() const { return tex; }

    // data members
    Texture*    tex;
    Vector3*    verts;
    VertexUV*   vertUVs;
    VertexN*    vertNs;
    VertexUVN*  vertUVNs;
};