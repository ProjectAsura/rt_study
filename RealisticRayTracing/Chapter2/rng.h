// RNG.h
#pragma once

class RNG
{
public:
    unsigned long long  seed;
    unsigned long long  mult;
    unsigned long long  llong_max;
    float               float_max;

    RNG(unsigned long long _seed = 7564231ULL)
    : seed(_seed)
    {
        mult = 62089911ULL;
        llong_max = 4294967295ULL;
        float_max = 4294967295.0f;
    }

    float operator() ()
    {
        seed = mult * seed;
        return float(seed % llong_max) / float_max;
    }
};
