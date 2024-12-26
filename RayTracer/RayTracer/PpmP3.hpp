#pragma once

#include <list>

#include "RGB256.hpp"

class PpmP3 final
{
	std::size_t imageWidth_, imageHeight_;

	std::list<RGB256>colors_;

	PpmP3(std::size_t imageWidth, std::size_t imageHeight, std::list<RGB256>colors);

public:
	PpmP3() = delete;

	[[nodiscard]] std::size_t getWidth() const { return imageWidth_; }
	[[nodiscard]] std::size_t getHeight() const { return imageHeight_; }
	[[nodiscard]] std::list<RGB256> getColors() const { return colors_; }

	class Builder final
	{
		std::size_t imageWidth_, imageHeight_;

		std::list<RGB256>accumulatedColors_;

	public:
		Builder(std::size_t imageWidth, std::size_t imageHeight);

		void clear();

		void add(RGB256 color);

		[[nodiscard]] PpmP3 createImage();

	};
};
