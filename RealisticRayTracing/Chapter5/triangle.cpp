// Triangle.cc

#include "triangle.h"


Triangle::Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, const rgb& col)
: p0(v0), p1(v1), p2(v2), texture(col)
{ /* DO_NOTHING */ }

bool Triangle::hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const
{
    auto A = p0.x() - p1.x();
    auto B = p0.y() - p1.y();
    auto C = p0.z() - p1.z();

    auto D = p0.x() - p2.x();
    auto E = p0.y() - p2.y();
    auto F = p0.z() - p2.z();

    auto G = ray.direction().x();
    auto H = ray.direction().y();
    auto I = ray.direction().z();

    auto J = p0.x() - ray.origin().x();
    auto K = p0.y() - ray.origin().y();
    auto L = p0.z() - ray.origin().z();

    auto EIHF = E * I - H * F;
    auto GFDI = G * F - D * I;
    auto DHEG = D * H - E * G;

    auto denom = (A * EIHF + B * GFDI + C * DHEG);

    auto beta = (J * EIHF + K * GFDI + L * DHEG) / denom;

    if (beta <= 0.0f || beta >= 1.0f)
    { return false; }

    auto AKJB = A * K - J * B;
    auto JCAL = J * C - A * L;
    auto BLKC = B * L - K * C;

    auto gamma = (I * AKJB + H * JCAL + G * BLKC) / denom;
    if (gamma <= 0.0f || beta + gamma >= 1.0f)
    { return false; }

    auto tval = -(F * AKJB + E * JCAL + D * BLKC) / denom;
    if (tval >= tmin && tval <= tmax)
    {
        record.t       = tval;
        record.normal  = unitVector(cross((p1 - p0), (p2 - p0)));
        record.hit_tex = &texture;
        return true;
    }

    return false;
}

bool Triangle::shadowHit(const Ray& ray, float tmin, float tmax, float time) const
{
    auto A = p0.x() - p1.x();
    auto B = p0.y() - p1.y();
    auto C = p0.z() - p1.z();

    auto D = p0.x() - p2.x();
    auto E = p0.y() - p2.y();
    auto F = p0.z() - p2.z();

    auto G = ray.direction().x();
    auto H = ray.direction().y();
    auto I = ray.direction().z();

    auto J = p0.x() - ray.origin().x();
    auto K = p0.y() - ray.origin().y();
    auto L = p0.z() - ray.origin().z();

    auto EIHF = E * I - H * F;
    auto GFDI = G * F - D * I;
    auto DHEG = D * H - E * G;

    auto denom = (A * EIHF + B * GFDI + C * DHEG);

    auto beta = (J * EIHF + K * GFDI + L * DHEG) / denom;

    if (beta <= 0.0f || beta >= 1.0f)
    { return false; }

    auto AKJB = A * K - J * B;
    auto JCAL = J * C - A * L;
    auto BLKC = B * L - K * C;

    auto gamma = (I * AKJB + H * JCAL + G * BLKC) / denom;
    if (gamma <= 0.0f || beta + gamma >= 1.0f)
    { return false; }

    auto tval = -(F * AKJB + E * JCAL + D * BLKC) / denom;

    return (tval >= tmin && tval <= tmax);
}
