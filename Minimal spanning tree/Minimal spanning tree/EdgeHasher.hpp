#pragma once
#include "Edge.hpp"

struct EdgeHasher final
{
	std::size_t operator()(const Edge& edge) const noexcept;
};