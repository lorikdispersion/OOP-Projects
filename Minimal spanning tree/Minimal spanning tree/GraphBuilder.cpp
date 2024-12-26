#include "GraphExceptions.hpp"
#include "Graph.hpp"

void Graph::Builder::insertVertex(const Vertex& vertex)
{
	const auto foundPair = vertices_.find(vertex.getId());
	if(foundPair == vertices_.end())
	{
		vertices_.insert({vertex.getId(), vertex});
	}
	else if(foundPair->second != vertex)
	{
		throw BadVertex{};
	}
}

void Graph::Builder::insertEdge(const Vertex& sVertex, const Vertex& eVertex)
{
	try {
		insertVertex(sVertex);
		insertVertex(eVertex);
	}
	catch (BadVertex&)	{
		throw BadEdge{};
	}
	edges_.insert({ sVertex, eVertex });
}

const IdToVertexMap& Graph::Builder::getVertices() noexcept
{
	return vertices_;
}

[[nodiscard]] std::size_t Graph::Builder::countVertices() const noexcept
{
	return vertices_.size();
}

[[nodiscard]] std::size_t Graph::Builder::countEdges() const noexcept
{
	return edges_.size();
}

Graph Graph::Builder::createGraph() const noexcept
{
	return Graph{ vertices_, edges_ };
}


