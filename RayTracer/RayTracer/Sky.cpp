#include "Sky.hpp"

RGB256 Sky::hit(const Ray& ray) const
{
    const Vector3d unitDirection = Vector3d::unitVector(ray.direction());
    const auto t = 0.5f * (unitDirection.y() + 1.0f);
    return {static_cast<std::size_t>(255 * (1.0f - t * 0.5f)),
    	static_cast<std::size_t>(255 * (1.0f - t * 0.3f)), 255};
}
