#include "Lambertian.hpp"

#include "HitRecord.hpp"

std::optional<std::pair<Attenuation, Ray>> Lambertian::scatter(const HitRecord& rec) const
{
    auto scatterDirection = rec.getNormal() + Vector3d::randomVectorInUnitSphere();
    if (scatterDirection.isNearZero())
        scatterDirection = rec.getNormal();
    return { { albedo_, Ray(rec.getPoint(), scatterDirection)  } };
}