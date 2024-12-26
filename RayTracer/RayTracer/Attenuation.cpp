#include "Attenuation.hpp"

#include "AttenuationExceptions.hpp"

Attenuation::Attenuation() : r_(0), g_(0), b_(0) {}


Attenuation::Attenuation(float r, float g, float b) : r_(r), g_(g), b_(b)
{
	if (r < 0.0f || r > 1.0f ||
		g < 0.0f || g > 1.0f ||
		b < 0.0f || b > 1.0f)
	{
		throw AttenuationCoefficientOutOfRange();
	}
}

Attenuation Attenuation::operator*(float t) const
{
	return { r_ * t, g_ * t,b_ * t };
}

Attenuation Attenuation::operator+(const Attenuation& attenuation) const
{
	return { r_ + attenuation.r_,
		g_ + attenuation.g_,
		b_ * attenuation.b_ };
}

Attenuation& Attenuation::operator+=(const Attenuation& attenuation)
{
	r_ += attenuation.r();
	g_ += attenuation.g();
	b_ += attenuation.b();
	return *this;
}

Attenuation& Attenuation::operator*=(Attenuation attenuation)
{
	r_ *= attenuation.r();
	g_ *= attenuation.g();
	b_ *= attenuation.b();
	return *this;
}

Attenuation Attenuation::operator*(const Attenuation& attenuation) const
{
	return { r_ * attenuation.r_, g_ * attenuation.g_, b_ * attenuation.b_ };
}