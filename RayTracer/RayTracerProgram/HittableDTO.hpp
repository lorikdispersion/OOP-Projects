#pragma once

#include "HittableNameConvertor.hpp"

class HittableDTO {
	HittableNameConvertor::Name name_;
protected:
	HittableDTO(HittableNameConvertor::Name name) { name_ = name; }
public:

	virtual ~HittableDTO() = default;

	[[nodiscard]] virtual HittableNameConvertor::Name getName() const { return name_; }
};
