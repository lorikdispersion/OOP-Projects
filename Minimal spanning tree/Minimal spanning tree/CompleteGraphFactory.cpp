#include <sstream>
#include <ostream>

#include "CompleteGraphFactory.hpp"

#include "GraphExceptions.hpp"
#include "ParserExceptions.hpp"


CompleteGraphFactory::CompleteGraphFactory(Parser parser) noexcept : parser_(std::move(parser)) {}

Graph CompleteGraphFactory::createGraph (std::istream& input) const
{
	IdToVertexMap vertices;
	Graph::Builder graphData;

	while (!input.eof()) {
		VertexData DTO = parser_.createVertexDataFromStream(input);
		try {
			graphData.insertVertex({ DTO.getId(), DTO.getX(), DTO.getY() });
		}
		catch (BadEdge&) {
			throw BadRow{};
		}
	}

	for (auto iterator_1{ graphData.getVertices().begin() }; iterator_1 != graphData.getVertices().end(); ++iterator_1)
	{
		for (auto iterator_2 = std::next(iterator_1); iterator_2 != graphData.getVertices().end(); ++iterator_2)
		{
			graphData.insertEdge(iterator_2->second, iterator_1->second);
		}
	}
	return graphData.createGraph();
}
