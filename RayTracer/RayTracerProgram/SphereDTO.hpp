#pragma once

#include "HittableDTO.hpp"

class SphereDTO : public HittableDTO {
	float x_;
	float y_;
	float z_;
	float r_;

public:
	explicit  SphereDTO(HittableNameConvertor::Name name, float x, float y, float z, float r) :
		HittableDTO(name), x_(x), y_(y), z_(z), r_(r) {}

	~SphereDTO() override = default;

	[[nodiscard]] float getX() const { return x_; }
	[[nodiscard]] float getY() const { return y_; }
	[[nodiscard]] float getZ() const { return z_; }
	[[nodiscard]] float getRadius() const { return r_; }
};