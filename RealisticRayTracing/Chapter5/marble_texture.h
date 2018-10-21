// MarbleTexture.h
#pragma once

#include "texture.h"
#include "solid_noise.h"


class MarbleTexture : public Texture
{
public:
    MarbleTexture(float stripes_per_unit, float _scale = 5.0f, int _octaves = 8)
    {
        freq = M_PI * stripes_per_unit;
        scale = _scale;
        octaves = _octaves;
        c0 = rgb(0.8f, 0.8f, 0.8f);
        c1 = rgb(0.4f, 0.2f, 0.1f);
        c2 = rgb(0.06f, 0.04f, 0.02f);
    }

    MarbleTexture
    (
        const rgb&  col0,
        const rgb&  col1,
        const rgb&  col2,
        float       stripes_per_unit,
        float       _scale = 3.0f,
        int         _octaves = 8
    )
        : c0(col0)
        , c1(col1)
        , c2(col2)
        , scale(_scale)
        , octaves(_octaves)
    {
        freq = M_PI * stripes_per_unit;
    }

    rgb value(const Vector2& uv, const Vector3& p) const override
    {
        auto temp = scale * solid_noise.turbulence(freq * p, octaves);
        auto t = 2.0f * fabs(sin(freq * p.x() + temp));

        if (t < 1.0f)
        { return (c1 * t + (1.0f - t) * c2); }
        else
        {
            t -= 1.0f;
            return (c0 * t + (1.0f - t) * c1);
        }
    }

    float       freq;
    float       scale;
    int         octaves;
    rgb         c0;
    rgb         c1;
    rgb         c2;
    SolidNoise  solid_noise;
};