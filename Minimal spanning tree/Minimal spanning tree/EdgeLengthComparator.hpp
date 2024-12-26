#pragma once
#include "Edge.hpp"

struct EdgesLengthComparator final
{
	bool operator()(const Edge& lhs, const Edge& rhs) const noexcept;
};