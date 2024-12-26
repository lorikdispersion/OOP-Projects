#pragma once

#include "Graph.hpp"


class MinimalSpanningTreeAlgorithm
{
public:
	virtual ~MinimalSpanningTreeAlgorithm() = default;
	[[nodiscard]] virtual Graph createSpanningTree(const Graph& graph) const = 0 ;
};

