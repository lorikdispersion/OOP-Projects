#include "HittableParser.hpp"

#include <sstream>
#include <stdexcept>

#include "SphereDTO.hpp"

namespace {
	enum class GeneralIndex : unsigned int
	{
		objectName = 0
	};

	enum class SphereIndex : unsigned int
	{
		x = 1, y = 2, z = 3, r = 4, size = 5
	};

	unsigned int indexToInt(GeneralIndex index)
	{
		return static_cast<unsigned int>(index);
	}

	unsigned int indexToInt(SphereIndex index)
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

std::shared_ptr<HittableDTO> HittableParser::parse(std::istream& input) const
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

	HittableNameConvertor convertor;

	switch (convertor.getName(parsedString[indexToInt(GeneralIndex::objectName)]))
	{
	case HittableNameConvertor::Name::Sphere:
		if (parsedString.size() != indexToInt(SphereIndex::size))
		{
			throw std::invalid_argument("Not enough arguments");
		}
		return std::make_shared<SphereDTO>(
			convertor.getName(parsedString[indexToInt(GeneralIndex::objectName)]),
			convertToFloatOrThrow(parsedString[indexToInt(SphereIndex::x)]),
			convertToFloatOrThrow(parsedString[indexToInt(SphereIndex::y)]),
			convertToFloatOrThrow(parsedString[indexToInt(SphereIndex::z)]),
			convertToFloatOrThrow(parsedString[indexToInt(SphereIndex::r)]));
	case HittableNameConvertor::Name::Incorrect:
		throw std::invalid_argument("UnknownObject");
	}
	return {};
}
