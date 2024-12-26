#pragma once

#include <unordered_map>
#include <unordered_set>

#include "EdgeHasher.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"

using IdToVertexMap = std::unordered_map<std::string, Vertex>;
using EdgesSet = std::unordered_set<Edge, EdgeHasher>;

class Graph final
{
	IdToVertexMap vertices_;
	EdgesSet edges_;

	Graph(IdToVertexMap vertices, EdgesSet edges) noexcept;

public:

	class Builder final
	{
		IdToVertexMap vertices_;
		EdgesSet edges_;
	public:
		void insertVertex(const Vertex& vertex);
		void insertEdge(const Vertex& sVertex, const Vertex& eVertex);
		[[nodiscard]] const IdToVertexMap& getVertices() noexcept;
		[[nodiscard]] Graph createGraph() const noexcept;
		[[nodiscard]] std::size_t countVertices() const noexcept;
		[[nodiscard]] std::size_t countEdges() const noexcept;
	};
	bool operator==(const Graph& vertex) const noexcept = default;
	[[nodiscard]] const IdToVertexMap& getVertices() const noexcept;
	[[nodiscard]] const EdgesSet& getEdges() const noexcept;
	[[nodiscard]] std::size_t countVertices() const noexcept;
	[[nodiscard]] std::size_t countEdges() const noexcept;

	//using Vertex_Vertex_Map = std::unordered_map<Vertex, Vertex, VertexHasher, Vertex_Equaler>;
};