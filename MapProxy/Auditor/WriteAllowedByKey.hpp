#pragma once

#include <unordered_set>

#include "WriteAccessDelegate.hpp"

class WriteAllowedByKey final : public WriteAccessDelegate
{
	std::unordered_set<std::string> allowedKeys_;
public:
	explicit WriteAllowedByKey(std::unordered_set<std::string> allowedKeys) noexcept
		: allowedKeys_(std::move(allowedKeys)) {}

	[[nodiscard]] bool canWrite(const std::string& key) override
	{
		return allowedKeys_.contains(key);
	}
};