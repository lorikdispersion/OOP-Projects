#pragma once

#include <string>

class EraseAccessDelegate
{
public:
	virtual ~EraseAccessDelegate() = default;

	[[nodiscard]] virtual bool canErase(const std::string& key) = 0;
};