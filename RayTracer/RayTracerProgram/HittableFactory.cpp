#include "HittableFactory.hpp"

#include <stdexcept>

#include "Sphere.hpp"
#include "SphereDTO.hpp"

std::shared_ptr<Hittable> HittableFactory::createHittable(HittableParser parser,
	std::istream& input, const std::shared_ptr<Material>& material)
{
	const auto hittableData = parser.parse(input);

	switch (hittableData->getName())
	{
	case HittableNameConvertor::Name::Sphere:
	{
		const auto sphereData = std::dynamic_pointer_cast<SphereDTO>(hittableData);
		return std::make_shared<Sphere>(
			Vector3d(sphereData->getX(), sphereData->getY(), sphereData->getZ()),
			sphereData->getRadius(), material);
	}
	case HittableNameConvertor::Name::Incorrect:
	{
		throw std::invalid_argument("Unknown material");
	}
	}
	return {};
}
