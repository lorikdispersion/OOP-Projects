#include "GraphsEdgesPrinter.hpp"
#include <ostream>

void GraphEdgesPrinter::printToStream(const Graph& graph, std::ostream& ostream) noexcept
{
	for (auto& it : graph.getEdges())
	{
		ostream << it.getStartVertex().getId()
			<< " - " << it.getEndVertex().getId() << std::endl;
	}
}