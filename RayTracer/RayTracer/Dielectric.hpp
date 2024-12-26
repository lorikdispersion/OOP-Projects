#pragma once

#include "Material.hpp"

class Dielectric : public Material {
	float refractionIndex_;

	static float reflectance(float cos, float refractionIndex);

public:
	explicit  Dielectric(float refractionIndex) : refractionIndex_(refractionIndex) {}

	[[nodiscard]] std::optional<std::pair<Attenuation, Ray>> scatter(
		const HitRecord& record) const override;
};