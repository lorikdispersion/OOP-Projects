#pragma once

#include <optional>
#include <stdexcept>

#include "Utilities.hpp"
#include "Vector3d.hpp"

class Ray {
    Vector3d origin_;
    Vector3d direction_;
public:
    Ray() = default;
    Ray(Vector3d origin, Vector3d direction);

    [[nodiscard]] Vector3d origin() const noexcept { return origin_; }
    [[nodiscard]] Vector3d direction() const noexcept { return direction_; }

    [[nodiscard]] Vector3d at(const float extension) const noexcept
    {
	    return origin_ + direction_ * extension;
    }

    bool operator==(const Ray&) const = default;
};
