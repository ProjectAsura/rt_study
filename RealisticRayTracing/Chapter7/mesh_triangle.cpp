// MeshTriangle.cc

#include "mesh.h"
#include "mesh_triangle.h"


MeshTriangleUV::MeshTriangleUV(Mesh* mesh, int p0, int p1, int p2)
: mesh_ptr(mesh)
{
    p[0] = p0;
    p[1] = p1;
    p[2] = p2;
}

bool MeshTriangleUV::hit(const Ray& ray, float tmin, float tmax, float time, HitRecord& record) const
{
    Vector3 p0((mesh_ptr->vertUVs[p[0]]).position);
    Vector3 p1((mesh_ptr->vertUVs[p[1]]).position);
    Vector3 p2((mesh_ptr->vertUVs[p[2]]).position);

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
        // if prim is hit, fill hit_rec
        auto alpha = 1.0f - beta - gamma;
        Vector2 u0((mesh_ptr->vertUVs[p[0]]).uv);
        Vector2 u1((mesh_ptr->vertUVs[p[1]]).uv);
        Vector2 u2((mesh_ptr->vertUVs[p[2]]).uv);

        record.uv       = Vector2(
                            alpha * u0.x() + beta * u1.x() + gamma * u2.x(),
                            alpha * u0.y() + beta * u1.y() + gamma * u2.y());
        record.hit_tex  = mesh_ptr->getTexture();
        record.t        = float(tval);
        record.normal   = unitVector(cross((p1 - p0), (p2 - p0)));

        return true;
    }

    return false;
}

bool MeshTriangleUV::shadowHit(const Ray& ray, float tmin, float tmax, float time) const 
{
    Vector3 p0((mesh_ptr->vertUVs[p[0]]).position);
    Vector3 p1((mesh_ptr->vertUVs[p[1]]).position);
    Vector3 p2((mesh_ptr->vertUVs[p[2]]).position);

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
