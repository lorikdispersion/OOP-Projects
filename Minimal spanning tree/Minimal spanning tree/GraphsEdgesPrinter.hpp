#pragma once

#include "Graph.hpp"

struct GraphEdgesPrinter final
{
	GraphEdgesPrinter() = delete;
	static void printToStream(const Graph& graph, std::ostream& ostream) noexcept;
};

