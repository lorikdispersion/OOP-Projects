#pragma once

class Vector3d final {
	float x_, y_, z_;
public:
	Vector3d();
	Vector3d(float x, float y, float z);

	[[nodiscard]] float x() const noexcept { return x_; }
	[[nodiscard]] float y() const noexcept { return y_; }
	[[nodiscard]] float z() const noexcept { return z_; }

	static Vector3d randomVector();
	static Vector3d randomVector(float min, float max);
	static Vector3d randomVectorInUnitSphere();
	static Vector3d randomVectorInUnitDisk(const Vector3d& normal);

	[[nodiscard]] Vector3d operator-() const { return { -x_, -y_, -z_ }; }

	[[nodiscard]] Vector3d& operator+=(const Vector3d& v);
	[[nodiscard]] Vector3d& operator*=(float t);
	[[nodiscard]] Vector3d& operator/=(float t);
	[[nodiscard]] bool operator==(const Vector3d& vector) const = default;

	[[nodiscard]] Vector3d operator+(const Vector3d& u) const;
	[[nodiscard]] Vector3d operator-(const Vector3d& u) const;
	[[nodiscard]] Vector3d operator*(float t) const;
	[[nodiscard]] Vector3d operator/(float t) const;

	[[nodiscard]] static float dot(const Vector3d& u, const Vector3d& v);
	[[nodiscard]] static Vector3d cross(const Vector3d& u, const Vector3d& v);

	[[nodiscard]] float length() const noexcept;
	[[nodiscard]] float lengthSquared() const noexcept;
	[[nodiscard]] static Vector3d unitVector(const Vector3d& u);

	[[nodiscard]] bool isNearZero() const;

	static Vector3d reflect(const Vector3d& direction, const Vector3d& normal);
	static Vector3d refract(const Vector3d& direction, const Vector3d& normal,
		float refractionIndex);
};