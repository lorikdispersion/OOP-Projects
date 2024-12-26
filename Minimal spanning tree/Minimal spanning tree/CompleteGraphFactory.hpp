#pragma once

#include "Graph.hpp"
#include "Parser.hpp"

class CompleteGraphFactory final
{
	Parser parser_;
public:
	explicit CompleteGraphFactory(Parser parser) noexcept;
	[[nodiscard]]Graph createGraph(std::istream& input) const;
};