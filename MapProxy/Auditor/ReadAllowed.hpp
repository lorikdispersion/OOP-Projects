#pragma once

#include "ReadAccessDelegate.hpp"

class ReadAllowed final : public ReadAccessDelegate
{
public:
	[[nodiscard]] bool canRead(const std::string& key) override { return true; }
};