// Sphere.cpp

#include "sphere.h"


Sphere::Sphere(const Vector3& pos, float r, const rgb& col)
: center    (pos)
, radius    (r)
, texture   (col)
{ /* DO_NOTHING */} 

bool Sphere::hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const
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
        record.normal  = unitVector(ray.origin() + float(t) * ray.direction() - center);
        record.hit_tex = &texture;
        return true;
    }

    return false;
}

bool Sphere::shadowHit(const Ray& ray, float tmin, float tmax, float time) const
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