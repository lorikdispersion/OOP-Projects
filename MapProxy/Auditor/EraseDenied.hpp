#pragma once

#include "EraseAccessDelegate.hpp"

class EraseDenied final : public EraseAccessDelegate
{
public:
	[[nodiscard]] bool canErase(const std::string& key) override { return false; }
};