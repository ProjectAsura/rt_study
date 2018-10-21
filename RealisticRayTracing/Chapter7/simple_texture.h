// SimpleTexture.h
#pragma once

#include "texture.h"


class SimpleTexture : public Texture
{
public:
    SimpleTexture(const rgb& c)
    : color(c)
    { /* DO_NOTHING */ }

    rgb value(const Vector2&, const Vector3&) const override
    { return color; }

    rgb color;
};
