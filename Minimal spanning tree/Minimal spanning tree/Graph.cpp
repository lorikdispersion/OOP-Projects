#include "Graph.hpp"

Graph::Graph(IdToVertexMap vertices, EdgesSet edges) noexcept :
vertices_(std::move(vertices)), edges_(std::move(edges)){}

[[nodiscard]] const IdToVertexMap& Graph::getVertices() const noexcept
{
	return vertices_;
}

[[nodiscard]] const EdgesSet& Graph::getEdges() const noexcept
{
	return edges_;
}

[[nodiscard]] std::size_t Graph::countVertices() const noexcept
{
	return vertices_.size();
}

[[nodiscard]] std::size_t Graph::countEdges() const noexcept
{
	return edges_.size();
}
