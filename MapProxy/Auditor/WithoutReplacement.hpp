#pragma once

#include "ReplacementDelegate.hpp"

class WithoutReplacement final : public ReplacementDelegate
{
public:
	[[nodiscard]] const std::string& getFakeValue(
		const std::string& key, const std::string& value) override {
		return value;
	}
};