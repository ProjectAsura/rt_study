// DynSphere.cpp

#include "dynsphere.h"


DynSphere::DynSphere(const Vector3& pos, float r, const rgb& col, float mintime, float maxtime)
: center    (pos)
, radius    (r)
, texture   (col)
, min_time  (mintime)
, max_time  (maxtime)
{ /* DO_NOTHING */ }

bool DynSphere::hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const
{
    auto new_center = getCenter(time);
    auto temp = ray.origin() - new_center;

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
        record.t        = float(t);
        record.normal   = unitVector(ray.origin() + float(t) * ray.direction() - new_center);
        record.hit_tex  = &texture;
        return true;
    }

    return false;
}

bool DynSphere::shadowHit(const Ray& ray, float tmin, float tmax, float time) const
{
    auto new_center = getCenter(time);
    auto temp = ray.origin() - new_center;

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

Vector3 DynSphere::getCenter(float time) const
{
    auto real_time = time * max_time + (1.0f - time) * min_time;
    return Vector3(
        center.x() + real_time,
        center.y() + real_time,
        center.z() + real_time);
}
