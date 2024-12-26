#include "Scene.hpp"

#include <stdexcept>

#include "Utilities.hpp"

Scene::Scene(std::shared_ptr<Background> background,
    std::list<std::shared_ptr<Hittable>> hittableObjects) :
	hittableObjects_(std::move(hittableObjects)), background_(std::move(background))
{}

std::optional<HitRecord> Scene::hitObject(
    const Ray& ray, float extensionMin, float extensionMax) const
{
    std::optional<HitRecord> answerRecord;
    auto closestSoFar = extensionMax;
    for (const auto& object : hittableObjects_)
    {
        auto tmpRecord = object.get()->hit(ray, extensionMin, closestSoFar);
        if (tmpRecord.has_value()) {
            answerRecord = tmpRecord;
            closestSoFar = tmpRecord.value().getExtension();
        }
    }
    return answerRecord;
}

RGB256 Scene::hitBackground(const Ray& ray) const
{
    return background_->hit(ray);
}

RGB256 Scene::getRayColor(const Ray& ray, std::size_t depth) const
{
    auto hitRecord = hitObject(ray, epsilon, infinity);
    std::size_t childRaysCounter = 0;
    Attenuation totalAttenuation(1, 1, 1);
    Ray actualRay = ray;
    while (hitRecord.has_value()) {
        if (childRaysCounter >= depth)
        {
            return { 0, 0, 0 };
        }

        auto attenuationAndScatteredRay =
            hitRecord.value().getHitResult();

        if (!attenuationAndScatteredRay.has_value())
        {
            return { 0, 0, 0 };
        }
        totalAttenuation *= attenuationAndScatteredRay.value().first;
        auto scattered = attenuationAndScatteredRay.value().second;
        actualRay = scattered;
        hitRecord = hitObject(scattered, epsilon, infinity);

        childRaysCounter++;
    }
    return hitBackground(actualRay) * totalAttenuation;
}

Scene::Builder::Builder(std::shared_ptr<Background> background):
    background_(std::move(background))
{
    if (!background_)
    {
        throw std::invalid_argument("Null pointer");
    }
}


void Scene::Builder::clear()
{
	accumulatedHittableObjects_.clear();
}

void Scene::Builder::add(const std::shared_ptr<Hittable>& object)
{
    if (!object)
    {
        throw std::invalid_argument("Null pointer");
    }
    accumulatedHittableObjects_.push_back(object);
}

Scene Scene::Builder::createScene()
{
	return { std::move(background_),  accumulatedHittableObjects_};
}