#include "MaterialFactory.hpp"

#include <stdexcept>

#include "Dielectric.hpp"
#include "DielectricDTO.hpp"
#include "Lambertian.hpp"
#include "LambertianDTO.hpp"
#include "Metal.hpp"
#include "MetalDTO.hpp"

std::shared_ptr<Material> MaterialFactory::createMaterial(
	MaterialParser parser, std::istream& input)
{
	const auto materialData = parser.parse(input);

	switch (materialData->getName())
	{
	case MaterialNameConvertor::Name::Dielectric:
	{
		const auto dielectricData = std::dynamic_pointer_cast<DielectricDTO>(materialData);
		return std::make_shared<Dielectric>(dielectricData->getRefractionIndex());
	}

	case MaterialNameConvertor::Name::Lambertian:
	{
		const auto lambertianData = std::dynamic_pointer_cast<LambertianDTO>(materialData);
		return std::make_shared<Lambertian>(
			Attenuation(lambertianData->getAlbedoR(), lambertianData->getAlbedoG(), lambertianData->getAlbedoB()));
	}
	case MaterialNameConvertor::Name::Metal:
	{
		const auto metalData = std::dynamic_pointer_cast<MetalDTO>(materialData);
		return std::make_shared<Metal>(
			Attenuation(metalData->getAlbedoR(), metalData->getAlbedoG(), metalData->getAlbedoB()),
			metalData->getFuzz());
	}
	case MaterialNameConvertor::Name::Incorrect:
	{
		throw std::invalid_argument("Unknown material");
	}
	}
	return {};
}
