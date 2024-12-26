#pragma once

#include "Ray.hpp"

class Camera
{
	Vector3d origin_;
	Vector3d lowerLeftCorner_;
	Vector3d horizontal_;
	Vector3d vertical_;
	Vector3d u_, v_, w_;
	float lensRadius_;

public:
	Camera (const Vector3d& lookFrom, const Vector3d& lookAt,
		const Vector3d& viewUp, float verticalFovDeg,
		float aspectRatio, float aperture, float focusDist);

	[[nodiscard]] Ray getRay(float horizontalOffset, float verticalOffset) const;

};