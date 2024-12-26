#pragma once

#include "Attenuation.hpp"

#include <cstddef>

class RGB256 final {
	std::size_t r_, g_, b_;

public:
	RGB256();
	RGB256(std::size_t r, std::size_t g, std::size_t b);

	[[nodiscard]] std::size_t r() const noexcept { return r_; }
	[[nodiscard]] std::size_t g() const noexcept { return g_; }
	[[nodiscard]] std::size_t b() const noexcept { return b_; }

	[[nodiscard]] RGB256 operator*(float t) const;
	[[nodiscard]] RGB256 operator+(const RGB256& color) const;

	RGB256& operator+=(const RGB256& color);
	RGB256& operator*=(const RGB256& color);

	[[nodiscard]] RGB256 operator*(const Attenuation& attenuation) const;

	[[nodiscard]] RGB256 gammaCorrection(float gamma) const;
};