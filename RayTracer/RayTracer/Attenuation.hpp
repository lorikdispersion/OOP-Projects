#pragma once

class Attenuation final {
	float r_, g_, b_;
public:
	Attenuation();
	Attenuation(float r, float g, float b);

	[[nodiscard]] float r() const noexcept { return r_; }
	[[nodiscard]] float g() const noexcept { return g_; }
	[[nodiscard]] float b() const noexcept { return b_; }

	[[nodiscard]] Attenuation operator*(float t) const;
	[[nodiscard]] Attenuation operator+(const Attenuation& attenuation) const;

	Attenuation& operator+=(const Attenuation& attenuation);
	Attenuation& operator*=(Attenuation attenuation);

	[[nodiscard]] Attenuation operator*(const Attenuation& attenuation) const;
};
