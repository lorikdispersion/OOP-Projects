#pragma once
#include <list>
#include <memory>

#include "Background.hpp"
#include "Hittable.hpp"

class Scene final {
    std::list<std::shared_ptr<Hittable>> hittableObjects_;
    std::shared_ptr<Background> background_;

    Scene(std::shared_ptr<Background> background,
        std::list<std::shared_ptr<Hittable>> hittableObjects);

    [[nodiscard]] std::optional<HitRecord> hitObject(const Ray& ray,
        float extensionMin, float extensionMax) const;

    [[nodiscard]] RGB256 hitBackground(const Ray& ray) const;

public:
    Scene() = delete;

    [[nodiscard]] RGB256 getRayColor(const Ray& ray, std::size_t depth) const;

    class Builder final
    {
        std::list<std::shared_ptr<Hittable>> accumulatedHittableObjects_;
        std::shared_ptr<Background> background_;
    public:
        Builder(std::shared_ptr<Background> background);

        void clear();

        void add(const std::shared_ptr<Hittable>& object);

        Scene createScene();
    };
};
