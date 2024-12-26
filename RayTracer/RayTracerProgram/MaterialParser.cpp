#include "MaterialParser.hpp"

#include <sstream>
#include <string>

#include "DielectricDTO.hpp"
#include "LambertianDTO.hpp"
#include "MetalDTO.hpp"

namespace {
	enum class GeneralIndex : unsigned int
	{
		materialName = 0
	};

	enum class LambertianIndex : unsigned int
	{
		albedoR = 1, albedoG = 2, albedoB = 3, size = 4
	};

	enum class DielectricIndex : unsigned int
	{
		refractionIndex = 1, size = 2
	};

	enum class MetalIndex : unsigned int
	{
		albedoR = 1, albedoG = 2, albedoB = 3, fuzz = 4, size = 5
	};

	unsigned int indexToInt(GeneralIndex index)
	{
		return static_cast<unsigned int>(index);
	}

	unsigned int indexToInt(LambertianIndex index)
	{
		return static_cast<unsigned int>(index);
	}

	unsigned int indexToInt(DielectricIndex index)
	{
		return static_cast<unsigned int>(index);
	}

	unsigned int indexToInt(MetalIndex index)
	{
		return static_cast<unsigned int>(index);
	}

	float convertToFloatOrThrow(const std::string& token)
	{
		std::stringstream ss(token);
		if (float number; !(ss >> number).fail())
		{
			return number;
		}
		throw std::invalid_argument("Cannot convert");
	}

}

std::shared_ptr<MaterialDTO> MaterialParser::parse(std::istream& input) const
{
	std::vector<std::string> parsedString;
	std::string token;

	std::string stringToParse;
	std::getline(input, stringToParse);
	std::stringstream inputSs(stringToParse);

	while (std::getline(inputSs, token, delimiter_)) {
		parsedString.push_back(token);
	}

	if (parsedString.empty())
	{
		throw std::invalid_argument("Empty row");
	}

	MaterialNameConvertor convertor;

	switch (convertor.readName(parsedString[indexToInt(GeneralIndex::materialName)]))
	{
	case MaterialNameConvertor::Name::Dielectric:
		if (parsedString.size() != indexToInt(DielectricIndex::size))
		{
			throw std::invalid_argument("Not enough arguments");
		}
		return std::make_shared<DielectricDTO>(
			convertor.readName(parsedString[indexToInt(GeneralIndex::materialName)]),
			convertToFloatOrThrow(parsedString[indexToInt(DielectricIndex::refractionIndex)]));

	case MaterialNameConvertor::Name::Metal:
		if (parsedString.size() != indexToInt(MetalIndex::size))
		{
			throw std::invalid_argument("Not enough arguments");
		}
		return std::make_shared<MetalDTO>(
			convertor.readName(parsedString[indexToInt(GeneralIndex::materialName)]),
			convertToFloatOrThrow(parsedString[indexToInt(MetalIndex::albedoR)]),
			convertToFloatOrThrow(parsedString[indexToInt(MetalIndex::albedoG)]),
			convertToFloatOrThrow(parsedString[indexToInt(MetalIndex::albedoB)]),
			convertToFloatOrThrow(parsedString[indexToInt(MetalIndex::fuzz)]));

	case MaterialNameConvertor::Name::Lambertian:
		if (parsedString.size() != indexToInt(LambertianIndex::size))
		{
			throw std::invalid_argument("Not enough arguments");
		}
		return std::make_shared<LambertianDTO>(
			convertor.readName(parsedString[indexToInt(GeneralIndex::materialName)]),
			convertToFloatOrThrow(parsedString[indexToInt(LambertianIndex::albedoR)]),
			convertToFloatOrThrow(parsedString[indexToInt(LambertianIndex::albedoG)]),
			convertToFloatOrThrow(parsedString[indexToInt(LambertianIndex::albedoB)]));
	
	case MaterialNameConvertor::Name::Incorrect:
		throw std::invalid_argument("Unknown material");
	}

	return {};
}
