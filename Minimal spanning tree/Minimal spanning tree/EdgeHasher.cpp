#include "VertexHasher.hpp"
#include "EdgeHasher.hpp"

std::size_t EdgeHasher::operator()(const Edge& edge) const noexcept
{
	constexpr VertexHasher hasher;
	return hasher.operator()(edge.getStartVertex()) * 137
		 + hasher.operator()(edge.getEndVertex()) * 667;
}