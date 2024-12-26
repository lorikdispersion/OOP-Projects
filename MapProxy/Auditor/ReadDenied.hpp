#pragma once

#include "ReadAccessDelegate.hpp"

class ReadDenied final : public ReadAccessDelegate
{
public:
	ReadDenied() = default;

	[[nodiscard]] bool canRead(const std::string& key) override { return false; }
};