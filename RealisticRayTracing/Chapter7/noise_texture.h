// NoiseTexxture.h
#pragma once

#include "texture.h"
#include "solid_noise.h"


class NoiseTexture : public Texture
{
public:
    NoiseTexture(float s = 1.0f)
    {
        scale = s;
        c0 = rgb(0.8f, 0.0f, 0.0f);
        c1 = rgb(0.0f, 0.0f, 0.8f);
    }

    NoiseTexture(const rgb& col0, const rgb& col1, float s = 1.0f)
    : scale (s)
    , c0    (col0)
    , c1    (col1)
    { /* DO_NOTHING */ }

    rgb value(const Vector2& uv, const Vector3& p) const override
    {
        auto t = (1.0f + solid_noise.noise(p * scale)) / 2.0f;
        return t * c0 + (1.0f - t) * c1;
    }

    float       scale;
    rgb         c0;
    rgb         c1;
    SolidNoise  solid_noise;
};
