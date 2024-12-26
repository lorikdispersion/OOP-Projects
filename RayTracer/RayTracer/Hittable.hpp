#pragma once

#include <optional>

#include "Ray.hpp"
#include "HitRecord.hpp"

class Hittable {
public:
    virtual ~Hittable() = default;
    [[nodiscard]] virtual std::optional<HitRecord> hit(
        const Ray& r, float extensionMin, float extensionMax) const = 0;
};