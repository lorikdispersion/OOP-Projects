#pragma once

#include <utility>

#include "Hittable.hpp"

class Sphere final : public Hittable {

    Vector3d center_;
    float radius_;
    std::shared_ptr<Material> material_;
public:
    Sphere(Vector3d center, float radius, std::shared_ptr<Material> material);
    ~Sphere() override = default;

    [[nodiscard]] std::optional<HitRecord> hit(
        const Ray& ray, float extensionMin, float extensionMax) const override;
};