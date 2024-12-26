#pragma once

#include "Background.hpp"

class Sky final : public Background
{
public:
	Sky() = default;

	~Sky() override = default;

	[[nodiscard]] RGB256 hit(const Ray& ray) const override;
};
