#pragma once

#include <string>

class Auditor
{
public:
	Auditor() = default;

	virtual ~Auditor() = default;

	[[nodiscard]] virtual bool canRead(const std::string& key) = 0;
	[[nodiscard]] virtual bool canWrite(const std::string& key) = 0;
	[[nodiscard]] virtual bool canErase(const std::string& key) = 0;

	[[nodiscard]] virtual const std::string& replaceValue(
		const std::string& key, const std::string& value) = 0;
};