#include "Parser.hpp"
#include "ParserExceptions.hpp"

#include <istream>
#include <optional>
#include <sstream>
#include <vector>

namespace
{
	std::optional<double> tryConvert(const std::string& token)
	{
		std::stringstream ss(token);
		if(double coord; !(ss >> coord).fail())
		{
			return coord;
		}
		return {};
	}
}


Parser::Parser(std::string delimiter) noexcept : delimiter_(std::move(delimiter)){}


VertexData Parser::createVertexDataFromStream(std::istream& input) const
{
	std::vector<std::string> parsedString;
	std::string stringToParse;
	std::getline(input, stringToParse);

	std::size_t start = 0;
	while (start < stringToParse.length())
	{
		std::size_t end = stringToParse.find(delimiter_, start);
		if (end - start > 0) {
			parsedString.push_back(stringToParse.substr(start, end - start));
		}
		if (end != std::string::npos) {
			start = end + delimiter_.length();
		}
		else {
			start = stringToParse.length();
		}
	}

	if (parsedString.size() != 3)
	{
		throw BadRow{};
	}

	auto vertexX = tryConvert(parsedString[1]);
	auto vertexY = tryConvert(parsedString[2]);

	if (!vertexX.has_value() || !vertexY.has_value())
	{
		throw BadRow{};
	}

	std::string vertexID = parsedString[0];

	return { vertexID, vertexX.value(), vertexY.value() };
}
