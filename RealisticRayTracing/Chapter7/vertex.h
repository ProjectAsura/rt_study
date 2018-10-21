// Vertex.h
#pragma once

#include "vector2.h"
#include "vector3.h"


struct VertexUV
{
    Vector3 position;
    Vector2 uv;
};

struct VertexN
{
    Vector3 position;
    Vector3 normal;
};

struct VertexUVN
{
    Vector3 position;
    Vector3 normal;
    Vector2 uv;
};

