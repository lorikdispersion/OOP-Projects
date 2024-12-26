#pragma once

#include "Material.hpp"

class Lambertian : public Material {
    Attenuation albedo_;
public:
    explicit Lambertian(Attenuation albedo) : albedo_(albedo) {}

    [[nodiscard]] std::optional<std::pair<Attenuation, Ray>> scatter(
        const HitRecord& rec) const override;
};