#include "Dielectric.hpp"

#include "HitRecord.hpp"

float Dielectric::reflectance(float cos, float refractionIndex)
{
	// Use Schlick's approximation for reflectance.
	auto r0 = (1 - refractionIndex) / (1 + refractionIndex);
	r0 = r0 * r0;
	return r0 + (1 - r0) * powf((1 - cos), 5);
}

std::optional<std::pair<Attenuation, Ray>> Dielectric::scatter(
	const HitRecord& record) const
{
	const auto refractionRatio = record.isFrontFace() ?
		1.0f / refractionIndex_ : refractionIndex_;

	const auto unitDirection = Vector3d::unitVector(record.getRay().direction());

	const float cosTheta = fminf(Vector3d::dot(
		-unitDirection, record.getNormal()), 1.0f);

	const float sinTheta = sqrtf(1.0f - cosTheta * cosTheta);

	const bool cannotRefract = refractionRatio * sinTheta > 1.0;
	Vector3d direction;

	if (cannotRefract || reflectance(cosTheta, refractionRatio) > randomFloat()) {
		direction = Vector3d::reflect(unitDirection, record.getNormal());
	}
	else {
		direction = Vector3d::refract(unitDirection, record.getNormal(), refractionRatio);
	}

	return{ {Attenuation(1.0, 1.0, 1.0),
		Ray(record.getPoint(), direction) } };
}