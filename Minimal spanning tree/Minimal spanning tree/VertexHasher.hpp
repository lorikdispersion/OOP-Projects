#pragma once
#include "Vertex.hpp"

struct VertexHasher final
{
	std::size_t operator()(const Vertex& vertex) const noexcept;
};
