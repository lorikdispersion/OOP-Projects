#pragma once

#include <string>

class WriteAccessDelegate
{
public:
	virtual ~WriteAccessDelegate() = default;

	[[nodiscard]] virtual bool canWrite(const std::string& key) = 0;
};