// Sample.h
#pragma once

#include <cmath>

class Vector2;

// 2D sampling
void random     (Vector2* samples, int sample_count);
void jitter     (Vector2* samples, int sample_count); // jitter assumes sample_count is a perfect square
void nrooks     (Vector2* samples, int sample_count);
void multiJitter(Vector2* samples, int sample_count);// multiJitter assumes sample_count is perfect square
void shuffle    (Vector2* samples, int sample_count);

void boxFilter  (Vector2* samples, int sample_count);
void tentFilter (Vector2* samples, int sample_count);
void cubicSplineFilter(Vector2* samples, int sample_count);


// 1D sampling
void random (float* samples, int sample_count);
void jitter (float* samples, int sample_count);
void shuffle(float* samples, int sample_count);


// helper function for cubicSplineFilter
inline float solve(float r)
{
    auto u = r;
    for(auto i=0; i<5; ++i)
    {
        u = (11.0f * r + u * u * (6.0f + u * (8.0f - 9.0f * u))) /
            (4.0f + 12.0f * u * (1.0f + u * (1.0f - u)));
    }

    return u;
}

// helper function for cubicSplineFilter
inline float cubicFilter(float x)
{
    if (x < 1.0f / 24.0f)
    { return pow(24.0f * x, 0.25f) - 2.0f; }
    else if (x < 0.5f)
    { return solve(24.0f * (x - 1.0f / 24.0f) / 11.0f) - 1.0f; }
    else if (x < 23.0f / 24.0f)
    { return 1.0f - solve(24.0f * (23.0f / 24.0f - x) / 11.0f); }
    else
    { return 2.0f - pow(24.0f * (1.0f - x), 0.25f); }
}