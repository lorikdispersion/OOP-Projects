#pragma once

#include "MininalSpanningTreeAlgorithm.hpp"

struct KruskalsAlgorithm : MinimalSpanningTreeAlgorithm
{
	[[nodiscard]] Graph createSpanningTree(const Graph& graph) const noexcept override;
};
