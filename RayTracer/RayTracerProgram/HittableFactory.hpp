#pragma once

#include "Hittable.hpp"
#include "HittableParser.hpp"


class HittableFactory final
{
public:
	HittableFactory() = delete;

	[[nodiscard]] static std::shared_ptr<Hittable> createHittable(HittableParser parser,
		std::istream& input, const std::shared_ptr<Material>& material);
};
