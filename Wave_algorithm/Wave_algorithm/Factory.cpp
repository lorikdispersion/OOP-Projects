#include "Factory.hpp"

#include <istream>
#include <sstream>

Labyrinth Labyrinth_Factory::create(std::istream& input)
{
	std::vector<std::vector<Labyrinth::Cell_Type>> tmp_matrix;
	while (input.peek() != EOF)
	{
		std::vector<std::string> parsed_string = parser_.get_parsed_string(input);
		std::vector<Labyrinth::Cell_Type> tmp_vector;
		tmp_vector.reserve(parsed_string.size());
		for (const auto& iterator : parsed_string)
		{
			tmp_vector.push_back(Labyrinth::Cell_Type_Dictionary::convert_char_to_cell_type(iterator[0]));
		}
		tmp_matrix.push_back(tmp_vector);
	}
	Labyrinth labyrinth{ tmp_matrix };
	return labyrinth;
}
