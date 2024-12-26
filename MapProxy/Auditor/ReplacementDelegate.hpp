#pragma once
#include <string>

class ReplacementDelegate
{
public:
	virtual ~ReplacementDelegate() = default;

	[[nodiscard]] virtual const std::string& getFakeValue
		(const std::string& key, const std::string& value) = 0;
};
