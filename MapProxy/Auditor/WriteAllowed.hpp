#pragma once

#include "WriteAccessDelegate.hpp"

class WriteAllowed final : public WriteAccessDelegate
{
public:
	[[nodiscard]] bool canWrite(const std::string& key) override { return true; }
};