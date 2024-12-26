#pragma once

#include <memory>
#include <utility>

#include "Material.hpp"

class HitRecord final {
    Vector3d point_;
    Ray ray_;
    float extension_;
    Vector3d normal_;
    std::shared_ptr<Material> material_;
    bool isFrontFace_;
public:
    HitRecord(Vector3d point, Vector3d normal, Ray ray, float extension, std::shared_ptr<Material> material,
		bool isFrontFace) :
        point_(point), ray_(ray), extension_(extension), normal_(normal),
		material_(std::move(material)),
        isFrontFace_(isFrontFace) {}

    [[nodiscard]] const Vector3d& getPoint() const noexcept
    {
        return point_;
    }

    [[nodiscard]] float getExtension() const noexcept
    {
        return extension_;
    }

    [[nodiscard]] Ray getRay() const noexcept
    {
        return ray_;
    }

    [[nodiscard]] const Vector3d& getNormal() const noexcept
    {
        return normal_;
    }

    [[nodiscard]] bool isFrontFace() const noexcept
    {
        return isFrontFace_ ;
    }

    [[nodiscard]] std::optional<std::pair<Attenuation, Ray>> getHitResult() const noexcept
    {
        return material_->scatter(*this);
    }
};
