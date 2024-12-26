#include "Ray.hpp"

Ray::Ray(Vector3d origin, Vector3d direction) :
    origin_(origin), direction_(direction)
{
    if (direction.isNearZero())
    {
        throw std::invalid_argument("Null direction vector");
    }
}