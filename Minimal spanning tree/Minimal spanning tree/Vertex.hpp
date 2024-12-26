#pragma once

#include <string>

class Vertex final
{
	std::string id_;
	double x_, y_;
public:
	Vertex(std::string id, double x, double y) noexcept;
	[[nodiscard]] const std::string& getId() const noexcept;
	[[nodiscard]] double getX() const noexcept;
	[[nodiscard]] double getY() const noexcept;
	bool operator==(const Vertex& vertex) const noexcept = default;
};