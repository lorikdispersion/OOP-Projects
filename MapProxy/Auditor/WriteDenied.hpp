#pragma once

#include "WriteAccessDelegate.hpp"

class WriteDenied final :public  WriteAccessDelegate
{
public:
	[[nodiscard]] bool canWrite(const std::string& key) override { return false; }
};