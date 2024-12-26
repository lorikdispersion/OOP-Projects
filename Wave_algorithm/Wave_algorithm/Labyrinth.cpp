#include "Labyrinth.hpp"

Labyrinth::Labyrinth(std::vector<std::vector<Cell_Type>> matrix): matrix_(std::move(matrix)) {}

std::vector<std::vector<Labyrinth::Cell_Type>>& Labyrinth::get_matrix()
{
	return matrix_;
}

Labyrinth::Cell_Type Labyrinth::Cell_Type_Dictionary::convert_char_to_cell_type(char litera)
{
	return static_cast<Cell_Type>(litera);
}

char Labyrinth::Cell_Type_Dictionary::convert_cell_type_to_char(Cell_Type cell)
{
	return static_cast<char>(cell);
}

void Labyrinth::output(std::ostream& ostream) const
{
	for(const auto& matrix_it: matrix_)
	{
		for(const auto vector_it: matrix_it)
		{
			ostream << Cell_Type_Dictionary::convert_cell_type_to_char(vector_it) << " ";
		}
		ostream << std::endl;
	}
}