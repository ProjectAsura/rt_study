// Texture.h
#pragma once

#include "vector2.h"
#include "vector3.h"
#include "rgb.h"


class Texture
{
public:
    // The Vector2 is UV coord and the Vector3 is the 3D hit point
    virtual rgb value(const Vector2& uv, const Vector3& pos) const = 0;
};