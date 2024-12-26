#include "RGB256.hpp"

#include <stdexcept>

RGB256::RGB256() : r_(0), g_(0), b_(0) {}

RGB256::RGB256(std::size_t r, std::size_t g, std::size_t b) : r_(r), g_(g), b_(b)
{
	if (r > 255 || g > 255 || b > 255) { throw std::invalid_argument("Color component out of range"); }
}

RGB256 RGB256::operator*(float t) const
{
	return { static_cast<std::size_t>(static_cast<float>(r_) * t),
		static_cast<std::size_t>(static_cast<float>(g_) * t),
		static_cast<std::size_t>(static_cast<float>(b_) * t), };
}

RGB256 RGB256::operator+(const RGB256& color) const
{
	return { r_ + color.r_, g_ + color.g_, b_ + color.b_ };
}

RGB256& RGB256::operator+=(const RGB256& color)
{
	r_ += color.r_;
	g_ += color.g_;
	b_ += color.b_;
	return *this;
}

RGB256& RGB256::operator*=(const RGB256& color)
{
	r_ *= color.r_;
	g_ *= color.g_;
	b_ *= color.b_;
	return *this;
}

RGB256 RGB256::operator*(const Attenuation& attenuation) const
{
	return { static_cast<std::size_t>(static_cast<float>(r_) * attenuation.r()),
		static_cast<std::size_t>(static_cast<float>(g_) * attenuation.g()),
		static_cast<std::size_t>(static_cast<float>(b_) * attenuation.b()), };
}

RGB256 RGB256::gammaCorrection(float gamma) const
{
	float unitR = static_cast<float>(r_) / 256.0f;
	float unitG = static_cast<float>(g_) / 256.0f;
	float unitB = static_cast<float>(b_) / 256.0f;

	unitR = powf(unitR, gamma);
	unitG = powf(unitG, gamma);
	unitB = powf(unitB, gamma);

	return { static_cast<std::size_t>(256 * unitR),
		static_cast<std::size_t>(256*unitG),
		static_cast<std::size_t>(256*unitB) };
}
