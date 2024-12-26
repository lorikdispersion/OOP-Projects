#pragma once

#include "Labyrinth.hpp"

class Find_Exit_Algorithm
{
public:
	virtual ~Find_Exit_Algorithm() = default;
	virtual void find_exit_in_labyrinth(Labyrinth& labyrinth, std::ostream& log_stream) const = 0;
};

class Wave_Algorithm final : public Find_Exit_Algorithm
{
public:
	void find_exit_in_labyrinth(Labyrinth& labyrinth, std::ostream& log_stream) const override;
};