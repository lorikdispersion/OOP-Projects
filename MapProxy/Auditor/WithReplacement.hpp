#pragma once

#include <unordered_map>

#include "ReplacementDelegate.hpp"

class WithReplacement final : public ReplacementDelegate
{
	std::unordered_map<std::string, std::string> keysToFakeValues_;
public:
	WithReplacement(std::unordered_map<std::string, std::string> pairsToReplace)
		: keysToFakeValues_(std::move(pairsToReplace)) {}

	[[nodiscard]] const std::string& getFakeValue(
		const std::string& key, const std::string& value) override
	{
		const auto foundPair = keysToFakeValues_.find(key);
		if (foundPair != keysToFakeValues_.end())
		{
			return foundPair->second;
		}
		return value;
	}
};