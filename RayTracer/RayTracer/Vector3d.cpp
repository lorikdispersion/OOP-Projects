#include "Vector3d.hpp"

#include "Utilities.hpp"
#include "Vector3dExceptions.hpp"

Vector3d::Vector3d() : x_(0), y_(0), z_(0) {}

Vector3d::Vector3d(float x, float y, float z) : x_(x), y_(y), z_(z) {}

Vector3d Vector3d::randomVector()
{
	return { randomFloat(), randomFloat(), randomFloat() };
}

Vector3d Vector3d::randomVector(float min, float max)
{
	return { randomFloat(min, max), randomFloat(min, max), randomFloat(min, max) };
}

Vector3d Vector3d::randomVectorInUnitSphere()
{
	const float alpha = randomFloat(0, 2 * pi);
	const float theta = randomFloat(0, pi);
	return { sinf(theta) * cosf(alpha), sinf(theta) * sinf(alpha),  cosf(theta) };
}

Vector3d Vector3d::randomVectorInUnitDisk(const Vector3d& normal)
{
	const Vector3d w = unitVector(cross(normal, { 1, 0 ,0 }));
	const Vector3d u = unitVector(cross(normal, { 0, 1 ,0 }));
	const Vector3d v = unitVector(cross(normal, { 0, 0 ,1 }));
	Vector3d radius1;

	if (!w.isNearZero()) { radius1 = w; }
	else if (!u.isNearZero()) { radius1 = u; }
	else if (!v.isNearZero()) { radius1 = v; }
	else { throw NormalIsZero(); }

	const auto radius2 = unitVector(cross(normal, radius1));

	const float alpha = randomFloat(0, 2 * pi);

	return radius1 * cosf(alpha) * randomFloat() + radius2 * cosf(alpha) * randomFloat();
}

Vector3d& Vector3d::operator+=(const Vector3d& v)
{
	x_ += v.x_;
	y_ += v.y_;
	z_ += v.z_;
	return *this;
}

Vector3d& Vector3d::operator*=(float t)
{
	x_ *= t;
	y_ *= t;
	z_ *= t;
	return *this;
}

Vector3d& Vector3d::operator/=(float t)
{
	return *this *= 1.0f / t;
}

float Vector3d::length() const noexcept
{
	return sqrtf(lengthSquared());
}

float Vector3d::lengthSquared() const noexcept
{
	return dot(*this, *this);
}

Vector3d Vector3d::operator+(const Vector3d& u) const
{
	return { x_ + u.x_, y_ + u.y_, z_ + u.z_ };
}

Vector3d Vector3d::operator-(const Vector3d& u) const
{
	return *this + -u;
}

Vector3d Vector3d::operator*(float t) const
{
	return { x_ * t, y_ * t, z_ * t };
}

Vector3d Vector3d::operator/(float t) const
{
	return *this * (1.0f / t);
}

float Vector3d::dot(const Vector3d& u, const Vector3d& v)
{
	return u.x_ * v.x_ + u.y_ * v.y_ + u.z_ * v.z_;
}

Vector3d Vector3d::cross(const Vector3d& u, const Vector3d& v)
{
	return { u.y_ * v.z_ - u.z_ * v.y_,
		u.z_ * v.x_ - u.x_ * v.z_,
		u.x_ * v.y_ - u.y_ * v.x_ };
}

Vector3d Vector3d::unitVector(const Vector3d& u)
{
	return u / u.length();
}

bool Vector3d::isNearZero() const
{
	return fabsf(x_) < epsilon && fabsf(y_) < epsilon && fabsf(z_) < epsilon;
}

Vector3d Vector3d::reflect(const Vector3d& vector, const Vector3d& normal)
{
	return vector - normal * 2 * dot(vector, normal);
}

Vector3d Vector3d::refract(const Vector3d& direction, const Vector3d& normal, float refractionIndex)
{
	const auto cosRayAndNormalAngle = fminf(dot(direction * -1.0f, normal), 1.0f);

	const Vector3d rayTanPart = (direction +
		normal * cosRayAndNormalAngle) * refractionIndex;

	const Vector3d rayNormalPart = normal *
		(-1.0f * sqrtf(fabsf(1.0f - rayTanPart.lengthSquared())));

	return rayNormalPart + rayTanPart;
}





