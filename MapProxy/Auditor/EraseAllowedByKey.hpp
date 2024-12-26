#pragma once

#include <unordered_set>

#include "EraseAccessDelegate.hpp"

class EraseAllowedByKey final : public EraseAccessDelegate
{
	std::unordered_set<std::string> allowedKeys_;
public:
	explicit EraseAllowedByKey(std::unordered_set<std::string> allowedKeys) noexcept
		: allowedKeys_(std::move(allowedKeys)) {}

	[[nodiscard]] bool canErase(const std::string& key) override
	{
		return allowedKeys_.contains(key);
	}
};