#pragma once

#include <ostream>

#include "RGB256.hpp"

inline std::ostream& operator<<(std::ostream& output, RGB256 color)
{
	output << color.r() << ' ' << color.g() << ' ' << color.b();
	return output;
}