#pragma once

#include "Hittable.hpp"
#include "RGB256.hpp"

class Background
{
public:
	virtual ~Background() = default;
	[[nodiscard]] virtual RGB256 hit(const Ray& ray) const = 0;
};
