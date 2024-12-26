#pragma once

#include "EraseAccessDelegate.hpp"

class EraseAllowed final : public EraseAccessDelegate
{
public:
	[[nodiscard]] bool canErase(const std::string& key) override { return true; }
};