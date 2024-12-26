#pragma once

#include <unordered_set>

#include "WriteAccessDelegate.hpp"

class WriteDeniedByKey final : public WriteAccessDelegate
{
	std::unordered_set<std::string> deniedKeys_;
public:
	explicit WriteDeniedByKey(std::unordered_set<std::string> deniedKeys) noexcept
		: deniedKeys_(std::move(deniedKeys)) {}

	[[nodiscard]] bool canWrite(const std::string& key) override
	{
		return !deniedKeys_.contains(key);
	}
};