#pragma once

#include "Labyrinth.hpp"
#include "Parser.hpp"
#include "Wave_algorithm.hpp"

class Factory
{
public:
	virtual ~Factory() = default;
	virtual Labyrinth create(std::istream& input) = 0;
};

class Labyrinth_Factory final : public  Factory
{
	Parser parser_;
public:
	explicit Labyrinth_Factory(Parser parser) : parser_(std::move(parser)) {}
	Labyrinth create(std::istream& input) override;
};