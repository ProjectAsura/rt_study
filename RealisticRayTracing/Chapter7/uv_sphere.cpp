// UVSphere.cc

#include "uv_sphere.h"


UVSphere::UVSphere(const Vector3& pos, float r, Texture* tex)
: center    (pos)
, radius    (r)
, texture   (tex)
{ /* DO_NOTHING */} 

bool UVSphere::hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const
{
    auto temp = ray.origin() - center;
    double a = dot(ray.direction(), ray.direction());
    double b = 2 * dot(ray.direction(), temp);
    double c = dot(temp, temp) - radius * radius;

    double discriminant = b * b - 4 * a * c;

    // first check to see if ray intersects sphere
    if (discriminant > 0)
    {
        discriminant = sqrt(discriminant);
        double t = (-b - discriminant) / (2 * a);

        // now check for valid interval
        if (t < tmin)
        { t = (-b + discriminant) / (2 * a); }
        if (t < tmin || t > tmax)
        { return false; }

        // we have a valid hit
        record.t       = float(t);
        record.hit_p   = (ray.origin() + float(t) * ray.direction());
        Vector3 n = record.normal = (record.hit_p - center) / radius;

        // calculate UV coordinate
        auto twopi = 6.28318530718f;
        auto theta = acos(n.z());
        auto phi   = atan2(n.y(), n.x());
        if (phi < 0.0f) phi += twopi;

        auto one_over_2pi = 0.159154943092f;
        auto one_over_pi  = 0.318309886184f;
        record.uv = Vector2(phi * one_over_2pi, float((M_PI - theta) * one_over_pi));
        record.hit_tex = texture;

        return true;
    }

    return false;
}

bool UVSphere::shadowHit(const Ray& ray, float tmin, float tmax, float time) const
{
    auto temp = ray.origin() - center;
    double a = dot(ray.direction(), ray.direction());
    double b = 2 * dot(ray.direction(), temp);
    double c = dot(temp, temp) - radius * radius;

    double discriminant = b * b - 4 * a * c;

    // first check to see if ray intersects sphere
    if (discriminant > 0)
    {
        discriminant = sqrt(discriminant);
        double t = (-b - discriminant) / (2 * a);

        // now check for valid interval
        if (t < tmin)
        { t = (-b + discriminant) / (2 * a); }
        if (t < tmin || t > tmax)
        { return false; }

        // we have a valid hit
        return true;
    }

    return false;
}