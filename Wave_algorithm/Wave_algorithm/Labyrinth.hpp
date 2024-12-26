#pragma once

#include <map>
#include <ostream>
#include <utility>
#include <vector>

class Labyrinth final
{
public:
	enum class Cell_Type : char {
		BLANK = '0',
		WALL = '1',
		HERO = '2',
		EXIT = '3',
		WAY = '*'
	};
	class Cell_Type_Dictionary final
	{
	public:
		static char convert_cell_type_to_char(Cell_Type cell);
		static Cell_Type convert_char_to_cell_type(char litera);
	};

	Labyrinth() = default;
	Labyrinth(std::vector<std::vector<Cell_Type>> matrix);
	~Labyrinth() = default;
	std::vector<std::vector<Cell_Type>>& get_matrix();
	void output(std::ostream& ostream) const;
private:
	std::vector<std::vector<Cell_Type>> matrix_;
};
