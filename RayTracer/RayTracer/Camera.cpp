#include "Camera.hpp"

#include <stdexcept>

#include "Utilities.hpp"

namespace
{
	void throwIfInvalidCameraProperty(float verticalFovDeg, float aspectRatio, float aperture,
		float focusDist)
	{
		if(verticalFovDeg <= 0)
		{
			throw std::invalid_argument("FOV <= 0");
		}
		if (aspectRatio <= 0)
		{
			throw std::invalid_argument("Aspect ratio <= 0");
		}
		if (aperture <= 0)
		{
			throw std::invalid_argument("Aperture <= 0");
		}
		if (focusDist <= 0)
		{
			throw std::invalid_argument("Focus distant <= 0");
		}
	}
}

Camera::Camera(
	const Vector3d& lookFrom, const Vector3d& lookAt, const Vector3d& viewUp,
	float verticalFovDeg, float aspectRatio, float aperture, float focusDist)
{
	throwIfInvalidCameraProperty(verticalFovDeg, aspectRatio, aperture, focusDist);

	const auto theta = degreesToRadians(verticalFovDeg);
	const auto viewportHeight = 2.0f * tanf(theta / 2);
	const auto viewportWidth = aspectRatio * viewportHeight;

	w_ = Vector3d::unitVector(lookFrom - lookAt);
	u_ = Vector3d::unitVector(Vector3d::cross(viewUp, w_));
	v_ = Vector3d::cross(w_, u_);

	origin_ = lookFrom;
	horizontal_ = u_ * focusDist * viewportWidth;
	vertical_ = v_ * focusDist * viewportHeight;
	lowerLeftCorner_ = origin_ - horizontal_ / 2 - vertical_ / 2 - w_ * focusDist;

	lensRadius_ = aperture / 2;
}

Ray Camera::getRay(float horizontalOffset, float verticalOffset) const
{
	const Vector3d randomDisk = Vector3d::randomVectorInUnitDisk({ 0,0,1 }) * lensRadius_;
	const Vector3d offset = u_ * randomDisk.x() + v_ * randomDisk.y();

	return { origin_ + offset,lowerLeftCorner_ +
		horizontal_ * horizontalOffset +
		vertical_ * verticalOffset - origin_ - offset };
}
