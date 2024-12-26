#include "Vertex.hpp"

Vertex::Vertex(std::string id, double x, double y) noexcept : id_(std::move(id)), x_(x), y_(y) {}

const std::string& Vertex::getId() const noexcept
{
	return id_;
}

double Vertex::getX() const noexcept
{
	return x_;
}

double Vertex::getY() const noexcept
{
	return y_;
}

//bool Vertex::equals_with_epsilon(const Vertex& vertex) const noexcept
//{
//	constexpr double epsilon = 1e-4;
//	return this->id_ == vertex.id_
//		&& abs(this->getX() - vertex.getX()) < epsilon
//		&& abs(this->getY() - vertex.getY()) < epsilon;
//}
