#pragma once

#include <memory>

#include "MaterialDTO.hpp"

class MaterialParser final
{
	char delimiter_;
public:
	MaterialParser(char delimiter = ' ') : delimiter_(delimiter){}

	std::shared_ptr<MaterialDTO> parse(std::istream& input) const;
};
