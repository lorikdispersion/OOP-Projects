#pragma once

#include "VertexData.hpp"

class Parser final
{
	std::string delimiter_;
public:
	explicit Parser(std::string delimiter) noexcept;
	[[nodiscard]] VertexData createVertexDataFromStream(std::istream & input) const;
};