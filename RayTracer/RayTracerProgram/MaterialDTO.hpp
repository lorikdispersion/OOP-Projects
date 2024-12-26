#pragma once

#include "MaterialNameConvertor.hpp"

class MaterialDTO {
	MaterialNameConvertor::Name name_;

protected:
	MaterialDTO(MaterialNameConvertor::Name name) { name_ = name; }

public:
    virtual ~MaterialDTO() = default;

	[[nodiscard]] virtual MaterialNameConvertor::Name getName() const { return name_; }
};
