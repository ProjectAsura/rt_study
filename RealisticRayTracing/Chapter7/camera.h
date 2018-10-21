// Camera.h
#pragma once

#include "ray.h"
#include "onb.h"


class Camera
{
public:
    Camera() = default;

    Camera(const Camera& value)
    : center        (value.center)
    , corner        (value.corner)
    , across        (value.across)
    , up            (value.up)
    , uvw           (value.uvw)
    , lens_radius   (value.lens_radius)
    , u0            (value.u0)
    , u1            (value.u1)
    , v0            (value.v0)
    , v1            (value.v1)
    , d             (value.d)
    { /* DO_NOTHING */ }

    Camera
    (
        Vector3 c,
        Vector3 gaze,
        Vector3 vup,
        float   aperture,
        float   left,
        float   right,
        float   bottom,
        float   top,
        float   distance
    )
    : center(c)
    , u0    (left)
    , u1    (right)
    , v0    (bottom)
    , v1    (top)
    , d     (distance)
    {
        lens_radius = aperture / 2.0f;
        uvw.initFromWV(-gaze, vup);
        corner = center + u0 * uvw.u() + v0 * uvw.v() - d * uvw.w();
        across = (u0 - u1) * uvw.u();
        up     = (v0 - v1) * uvw.v();
    }

    // a and b are the pixel positions
    // xi1 and xi2 are the lens samples in the range (0, 1)^2
    Ray getRay(float a, float b, float xi1, float xi2)
    {
        Vector3 origin = center 
                        + 2.0f * (xi1 - 0.5f) * lens_radius * uvw.u()
                        + 2.0f * (xi2 - 0.5f) * lens_radius * uvw.v();
        Vector3 target = corner + across * a + up * b;

        return Ray(origin, unitVector(target - origin));
    }

private:
    Vector3 center;
    Vector3 corner;
    Vector3 across;
    Vector3 up;
    ONB     uvw;
    float   lens_radius;
    float   u0;
    float   u1;
    float   v0;
    float   v1;
    float   d;
};