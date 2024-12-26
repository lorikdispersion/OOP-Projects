#pragma once
#include "HitRecord.hpp"
#include "Material.hpp"

class Metal : public Material {
    Attenuation albedo_;
    float fuzz_;
public:
    Metal(Attenuation albedo, float fuzz) : albedo_(albedo),fuzz_(fuzz)
    {}

    [[nodiscard]] std::optional<std::pair<Attenuation, Ray>> scatter(
        const HitRecord& record) const override;
};
