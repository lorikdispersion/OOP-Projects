#include "VertexHasher.hpp"

std::size_t VertexHasher::operator()(const Vertex& vertex) const noexcept
{
	return std::hash<std::string>{}(vertex.getId())
			  + std::hash<double>{}(vertex.getX()) * 801
			  + std::hash<double>{}(vertex.getY()) * 997;
}
