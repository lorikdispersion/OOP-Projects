#pragma once

#include <memory>

#include "HittableDTO.hpp"

class HittableParser final
{
	char delimiter_;
public:
	HittableParser(char delimiter = ' ') : delimiter_(delimiter) {}

	std::shared_ptr<HittableDTO> parse(std::istream& input) const;
};
