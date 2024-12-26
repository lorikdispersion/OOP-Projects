#include "Sphere.hpp"

#include <stdexcept>

Sphere::Sphere(Vector3d center, float radius, std::shared_ptr<Material> material) :
    center_(center), radius_(radius), material_(std::move(material))
{
    if(!material_)
    {
        throw std::invalid_argument("Null pointer");
    }
}


auto Sphere::hit(const Ray& ray, float extensionMin, float extensionMax) const -> std::optional<HitRecord>
{
	const Vector3d originMinusCenter = ray.origin() - center_;
    const auto a = ray.direction().lengthSquared();
    const auto halfB = Vector3d::dot(originMinusCenter,ray.direction());
	const auto c = originMinusCenter.lengthSquared() - radius_ * radius_;

	const auto discriminant = halfB * halfB - a * c;
    if (discriminant < 0) { return std::nullopt; }
	const auto sqrtOfDiscriminant = sqrtf(discriminant);

    auto root = (-halfB - sqrtOfDiscriminant) / a;
    if (root <= extensionMin || extensionMax < root) {
        root = (-halfB + sqrtOfDiscriminant) / a;
        if (root <= extensionMin || extensionMax < root) {
            return std::nullopt;
        }
    }

	const auto point = ray.at(root);
	const auto outwardNormal = (point - center_)/radius_;
    const auto frontFace = Vector3d::dot(ray.direction(),outwardNormal) < 0;
    const auto normal = frontFace ? outwardNormal : -outwardNormal;

    return HitRecord{ point,  normal, ray,root, material_, frontFace};
}
