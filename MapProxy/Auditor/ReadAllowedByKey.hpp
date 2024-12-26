#pragma once

#include <unordered_set>

#include "ReadAccessDelegate.hpp"

class ReadAllowedByKey final : public ReadAccessDelegate
{
	std::unordered_set<std::string> allowedKeys_;
public:
	explicit ReadAllowedByKey(std::unordered_set<std::string> allowedKeys) noexcept
		: allowedKeys_(std::move(allowedKeys)){}

	[[nodiscard]] bool canRead(const std::string& key) override
	{
		return allowedKeys_.contains(key);
	}
};