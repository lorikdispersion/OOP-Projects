#pragma once

#include <unordered_set>

#include "EraseAccessDelegate.hpp"

class EraseDeniedByKey final : public EraseAccessDelegate
{
	std::unordered_set<std::string> deniedKeys_;
public:
	explicit EraseDeniedByKey(std::unordered_set<std::string> deniedKeys) noexcept
		: deniedKeys_(std::move(deniedKeys)) {}

	[[nodiscard]] bool canErase(const std::string& key) override
	{
		return !deniedKeys_.contains(key);
	}
};