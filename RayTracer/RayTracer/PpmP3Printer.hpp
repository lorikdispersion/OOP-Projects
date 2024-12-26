#pragma once

#include <ostream>

#include "PpmP3.hpp"
#include "RGB256ColorPrinter.hpp"

inline std::ostream& operator<<(std::ostream& output, PpmP3 image)
{
	output << "P3" << std::endl << image.getWidth() << ' ' <<
		image.getHeight() << std::endl << "255" << std::endl;
	for(const auto& it: image.getColors())
	{
		output << it << std::endl;
	}
	return output;
}