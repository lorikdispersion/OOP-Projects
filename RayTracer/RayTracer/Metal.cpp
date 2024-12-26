#include "Metal.hpp"

std::optional<std::pair<Attenuation, Ray>> Metal::scatter(const HitRecord& record) const
{
    const Vector3d reflected = Vector3d::reflect(
        Vector3d::unitVector(record.getRay().direction()), record.getNormal());

    const auto scattered = Ray(record.getPoint(),
        reflected + Vector3d::randomVectorInUnitSphere() * fuzz_);
    if (Vector3d::dot(scattered.direction(), record.getNormal()) <= 0) {
        return std::nullopt;
    }
    return { {albedo_, scattered} };
}

