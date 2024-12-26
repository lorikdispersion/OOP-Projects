#pragma once

#include <string>

class ReadAccessDelegate
{
public:
	virtual ~ReadAccessDelegate() = default;

	[[nodiscard]] virtual bool canRead(const std::string& key) = 0;
};