#pragma once
#include <string>

class VertexData final
{
	std::string vertexId_;
	double vertexX_;
	double vertexY_;
public:
	VertexData(std::string id, double x, double y);
	[[nodiscard]] const std::string& getId() const noexcept;
	[[nodiscard]] double getX() const noexcept;
	[[nodiscard]] double getY() const noexcept;
};
