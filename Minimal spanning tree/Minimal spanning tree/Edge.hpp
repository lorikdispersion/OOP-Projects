#pragma once

#include "Vertex.hpp"

class Edge final
{
	Vertex startVertex_;
	Vertex endVertex_;
	double length_;
public:
	Edge(Vertex sVertex, Vertex eVertex);
	[[nodiscard]] double getLength() const noexcept;
	[[nodiscard]] const Vertex& getStartVertex() const noexcept;
	[[nodiscard]] const Vertex& getEndVertex() const noexcept;
	bool operator==(const Edge& edge) const noexcept = default;
};




