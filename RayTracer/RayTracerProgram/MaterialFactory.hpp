#pragma once

#include "Material.hpp"
#include "MaterialParser.hpp"

class MaterialFactory final
{
public:
	MaterialFactory() = delete;

	[[nodiscard]] static std::shared_ptr<Material> createMaterial(
		MaterialParser parser, std::istream& input);
};
