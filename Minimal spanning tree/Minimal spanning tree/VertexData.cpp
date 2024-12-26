#include "VertexData.hpp"

VertexData::VertexData(std::string id, double x, double y) : vertexId_(std::move(id)), vertexX_(x), vertexY_(y){}

const std::string& VertexData::getId() const noexcept
{
	return vertexId_;
}

double VertexData::getX() const noexcept
{
	return vertexX_;
}

double VertexData::getY() const noexcept
{
	return vertexY_;
}