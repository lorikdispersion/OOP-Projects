#pragma once

#include <unordered_set>

#include "ReadAccessDelegate.hpp"

class ReadDeniedByKey final : public ReadAccessDelegate
{
	std::unordered_set<std::string> deniedKeys_;
public:
	explicit ReadDeniedByKey(std::unordered_set<std::string> deniedKeys) noexcept
		: deniedKeys_(std::move(deniedKeys)) {}

	[[nodiscard]] bool canRead(const std::string& key) override
	{
		return !deniedKeys_.contains(key);
	}
};