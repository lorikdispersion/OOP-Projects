#include "PpmP3.hpp"

#include <utility>

#include "PpmP3Exceptions.hpp"

PpmP3::PpmP3(std::size_t imageWidth, std::size_t imageHeight, std::list<RGB256> colors):
	imageWidth_(imageWidth), imageHeight_(imageHeight), colors_(std::move(colors))
{
	if(colors_.size() != imageHeight * imageWidth)
	{
		throw IncorrectNumberOfPixels();
	}
}

PpmP3::Builder::Builder(std::size_t imageWidth, std::size_t imageHeight):
	imageWidth_(imageWidth), imageHeight_(imageHeight) {}

void PpmP3::Builder::add(RGB256 color)
{
	accumulatedColors_.push_back(color);
}

void PpmP3::Builder::clear()
{
	accumulatedColors_.clear();
}

PpmP3 PpmP3::Builder::createImage()
{
	return { imageWidth_, imageHeight_, accumulatedColors_ };
}