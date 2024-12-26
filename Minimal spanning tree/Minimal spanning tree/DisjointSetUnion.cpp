#include "DisjointSetUnion.hpp"
#include "DisjointSetUnionExceptions.hpp"

void DisjointSetUnion::changeDeligate(const Vertex& vertex, const Vertex& newDeligate)
{
	const auto foundPair = verticesToDeligates_.find(vertex);
	if(foundPair == verticesToDeligates_.end()) {
		throw VertexNotInSet{};
	}
	foundPair->second = newDeligate;
}

Vertex DisjointSetUnion::getParent(const Vertex& vertex) const
{
	const auto foundPair = verticesToDeligates_.find(vertex);
	if(foundPair == verticesToDeligates_.end()) {
		throw VertexNotInSet{};
	}
	return foundPair->second;
}

void DisjointSetUnion::insertNewVertexToDeligate(const Vertex& vertex, const Vertex& deligate)
{
	if(verticesToDeligates_.contains(vertex)) {
		throw VertexAlreadyInSet{};
	}
	verticesToDeligates_.insert({ vertex, deligate });
}

std::unordered_map<Vertex, Vertex, VertexHasher> DisjointSetUnion::getVerticesToDeligates() const noexcept
{
	return verticesToDeligates_;
}
