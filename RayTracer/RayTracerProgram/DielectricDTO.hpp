#pragma once

#include "MaterialDTO.hpp"

class DielectricDTO : public MaterialDTO {
	float refractionIndex_;

public:
	explicit  DielectricDTO(MaterialNameConvertor::Name name, float refractionIndexData):
	MaterialDTO(name), refractionIndex_(refractionIndexData) {}

	~DielectricDTO() override = default;

	[[nodiscard]] float getRefractionIndex() const { return refractionIndex_; }
};