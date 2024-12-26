#pragma once

#include "Attenuation.hpp"
#include <optional>
#include "Ray.hpp"


class HitRecord;

class Material {
public:
    virtual ~Material() = default;

    [[nodiscard]] virtual std::optional<std::pair<Attenuation, Ray>> scatter(
        const HitRecord& record) const = 0;
};
