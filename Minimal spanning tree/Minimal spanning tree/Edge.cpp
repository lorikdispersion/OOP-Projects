#include "Edge.hpp"
#include "GraphExceptions.hpp"

Edge::Edge(Vertex sVertex, Vertex eVertex): startVertex_(std::move(sVertex)), endVertex_(std::move(eVertex))
{
	if(startVertex_.getId() == endVertex_.getId()) {
		throw BadVertex{};
	}

	if (startVertex_.getId() > endVertex_.getId()) {
		std::swap(startVertex_, endVertex_);
	}

	const double dx = startVertex_.getX() - endVertex_.getX();
	const double dy = startVertex_.getY() - endVertex_.getY();

	length_ = sqrt(pow(dx, 2) + pow(dy, 2));

}

double Edge::getLength() const noexcept
{
	return length_;
}

const Vertex& Edge::getStartVertex() const noexcept
{
	return startVertex_;
}

const Vertex& Edge::getEndVertex() const noexcept
{
	return endVertex_;
}