#pragma once
#include <unordered_map>

#include "VertexHasher.hpp"
#include "Vertex.hpp"

class DisjointSetUnion final
{
	std::unordered_map<Vertex, Vertex, VertexHasher> verticesToDeligates_;
public:
	DisjointSetUnion() = default;
	[[nodiscard]] Vertex getParent(const Vertex& vertex) const;
	void changeDeligate(const Vertex& vertex, const Vertex& newDeligate);
	void insertNewVertexToDeligate(const Vertex& vertex, const Vertex& Deligate);
	[[nodiscard]] std::unordered_map<Vertex, Vertex, VertexHasher> getVerticesToDeligates() const noexcept;
};
