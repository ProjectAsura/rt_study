// Sample.cc

#include "sample.h"
#include "vector2.h"
#include <cstdlib>

namespace {

double drand()
{ return double(rand() / RAND_MAX); }

float frand()
{ return float(drand()); }

} // namespace


void random(Vector2* samples, int sample_count)
{
    for(auto i=0; i<sample_count; ++i)
    {
        samples[i].setX(frand());
        samples[i].setY(frand());
    }
}

// assumes sample_count is a perfect square
void jitter(Vector2* samples, int sample_count)
{
    auto sqrt_samples = int(sqrt(sample_count));
    for(auto i=0; i<sqrt_samples; ++i)
    {
        for(auto j=0; j<sqrt_samples; ++j)
        {
            auto x = (double(i) + drand()) / double(sqrt_samples);
            auto y = (double(j) + drand()) / double(sqrt_samples);
            samples[i * sqrt_samples + j].setX(float(x));
            samples[i * sqrt_samples + j].setY(float(y));
        }
    }
}

void nrooks(Vector2* samples, int sample_count)
{
    for(auto i=0; i<sample_count; ++i)
    {
        samples[i].setX(float((double(i) + drand()) / double(sample_count)));
        samples[i].setY(float((double(i) + drand()) / double(sample_count)));
    }

    // shuffle the x coords.
    for(auto i=sample_count - 2; i >= 0; i--)
    {
        auto target = int(drand() * double(i));
        auto temp = samples[i + 1].x();
        samples[i + 1].setX(samples[target].x());
        samples[target].setX(temp);
    }
}

// assumes sample_count is a perfect square
void multiJitter(Vector2* samples, int sample_count)
{
    auto sqrt_samples = int(sqrt(sample_count));
    auto subcell_width = 1.0f / float(sample_count);

    // Initialize points to the "canonical" mult-jittered pattern
    for(auto i=0; i<sqrt_samples; ++i)
    {
        for(auto j=0; j<sqrt_samples; ++j)
        {
            samples[i * sqrt_samples + j].e[0] = float(
                  i * sqrt_samples * subcell_width
                + j * subcell_width + drand() * subcell_width);
            samples[i * sqrt_samples + j].e[1] = float(
                  j * sqrt_samples * subcell_width
                + i * subcell_width + drand() * subcell_width);
        }
    }

    // shuffle  x coords within each column and y coords within each row
    for(auto i=0; i<sqrt_samples; ++i)
    {
        for(auto j=0; j<sqrt_samples; ++j)
        {
            auto k = j + int(drand() * (sqrt_samples - j - 1));
            auto t = samples[i * sqrt_samples + j].e[0];
            samples[i * sqrt_samples + j].e[0] = samples[i * sqrt_samples + k].e[0];
            samples[i * sqrt_samples + k].e[0] = t;

            k = j + int(drand() * (sqrt_samples - j - 1));
            t = samples[j * sqrt_samples + i].e[1];
            samples[j * sqrt_samples + i].e[1] = samples[k * sqrt_samples + i].e[1];
            samples[k * sqrt_samples + i].e[1] = t;
        }
    }
}

void shuffle(Vector2* samples, int sample_count)
{
    for(auto i=sample_count - 2; i>=0; i--)
    {
        auto target = int(drand() * double(i));
        auto temp = samples[i + 1];
        samples[i + 1] = samples[target];
        samples[target] = temp;
    }
}

void boxFilter(Vector2* samples, int sample_count)
{
    for(auto i=0; i<sample_count; ++i)
    {
        samples[i].setX(samples[i].x() - 0.5f);
        samples[i].setY(samples[i].y() - 0.5f);
    }
}

void tentFilter(Vector2* samples, int sample_count)
{
    for(auto i=0; i<sample_count; ++i)
    {
        auto x = samples[i].x();
        auto y = samples[i].y();

        if (x < 0.5f) samples[i].setX(float(sqrt(2.0 * double(x)) - 1.0f));
        else samples[i].setX(1.0f - float(sqrt(2.0 - 2.0 * double(x))));

        if (y < 0.5f) samples[i].setY(float(sqrt(2.0 * double(y)) - 1.0f));
        else samples[i].setY(1.0f - float(sqrt(2.0 - 2.0f * double(y))));
    }
}

void cubicSplineFilter(Vector2* samples, int sample_count)
{
    for(auto i=0; i<sample_count; ++i)
    {
        auto x = samples[i].x();
        auto y = samples[i].y();

        samples[i].e[0] = cubicFilter(x);
        samples[i].e[1] = cubicFilter(y);
    }
}

void random(float* samples, int sample_count)
{
    for(auto i=0; i<sample_count; ++i)
    { samples[i] = frand(); }
}

void jitter(float* samples, int sample_count)
{
    for(auto i=0; i<sample_count; ++i)
    { samples[i] = float((double(i) + drand()) / double(sample_count)); }
}

void shuffle(float* samples, int sample_count)
{
    for(auto i=sample_count - 2; i>=0; i--)
    {
        auto target = int(drand() * double(i));
        auto temp = samples[i + 1];
        samples[i + 1] = samples[target];
        samples[target] = temp;
    }
}