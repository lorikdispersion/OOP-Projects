#include "Wave_algorithm.hpp"

#include <sstream>

namespace
{

	void fill_auxiliary_grid_with_zeros(std::vector<std::vector<std::size_t>>& grid, Labyrinth& labyrinth)
	{
		grid.reserve(labyrinth.get_matrix().size());
		for (auto& i : labyrinth.get_matrix())
		{
			std::vector<std::size_t> tmp_vector_w_zeros(i.size());
			std::fill(tmp_vector_w_zeros.begin(), tmp_vector_w_zeros.end(), 0);
			grid.push_back(tmp_vector_w_zeros);
		}
	}

	bool check_labyrinth_is_correct(Labyrinth& labyrinth)
	{
		for (std::size_t y = 0; y < labyrinth.get_matrix().size(); y++)
		{
			for (std::size_t x = 0; x < labyrinth.get_matrix()[y].size(); x++)
			{
				if ((x == 0 || x == labyrinth.get_matrix()[y].size() - 1
					|| y == 0 || y == labyrinth.get_matrix().size() - 1)
					&& labyrinth.get_matrix()[y][x] != Labyrinth::Cell_Type::WALL
					&& labyrinth.get_matrix()[y][x] != Labyrinth::Cell_Type::EXIT)
				{
					return false;
				}
			}
		}
		return true;
	}

	std::pair < std::size_t, std::size_t> find_coords_by_cell_type(Labyrinth& labyrinth, Labyrinth::Cell_Type cell_type, bool& flag)
	{
		flag = false;
		for (std::size_t y = 0; y < labyrinth.get_matrix().size(); y++)
		{
			for (std::size_t x = 0; x < labyrinth.get_matrix()[y].size(); x++)
			{
				if (labyrinth.get_matrix()[y][x] == cell_type)
				{
					flag = true;
					return { y, x };
				}
			}
		}
		return { 0,0 };
	}

	void spread_wave(Labyrinth& labyrinth, std::vector<std::vector<std::size_t>>& grid, 
		const std::pair<std::size_t, std::size_t>& hero_coords, const std::pair<std::size_t, std::size_t>& exit_coords,
		const std::vector <std::pair<int, int>>& dydx)
	{
		bool the_wave_can_spread;
		std::size_t actual_tag = 1;
		grid[hero_coords.first][hero_coords.second] = actual_tag;

		do
		{
			the_wave_can_spread = false;
			for (std::size_t y = 0; y < grid.size(); y++)
			{
				for (std::size_t x = 0; x < grid[y].size(); x++)
				{
					if (grid[y][x] == actual_tag)
					{
						for (const auto& shift_it : dydx)
						{
							const std::size_t near_y = y + shift_it.first;
							const std::size_t near_x = x + shift_it.second;

							if ((labyrinth.get_matrix()[near_y][near_x] == Labyrinth::Cell_Type::BLANK ||
								labyrinth.get_matrix()[near_y][near_x] == Labyrinth::Cell_Type::EXIT)
								&& grid[near_y][near_x] == 0)
							{
								the_wave_can_spread = true;
								grid[near_y][near_x] = actual_tag + 1;
							}
						}
					}
				}
			}
			actual_tag++;
		} while (the_wave_can_spread && grid[exit_coords.first][exit_coords.second] == 0);
	}
	void construct_path(Labyrinth& labyrinth, std::vector<std::vector<std::size_t>>& grid, 
		std::vector<std::pair<std::size_t, std::size_t>>& path,
		const std::pair<std::size_t, std::size_t>& hero_coords, const std::pair<std::size_t, std::size_t>& exit_coords,
		const std::vector <std::pair<int, int>>& dydx)
	{
		std::size_t actual_tag = grid[exit_coords.first][exit_coords.second];

		std::pair new_cell_in_path{ exit_coords.first, exit_coords.second };

		while (actual_tag > 1)
		{
			path.push_back(new_cell_in_path);
			actual_tag--;
			for (const auto& shift_it : dydx)
			{
				const std::size_t near_y = new_cell_in_path.first + shift_it.first;
				const std::size_t near_x = new_cell_in_path.second + shift_it.second;
				if (near_y >= 0 && near_x >= 0 && near_y < grid.size() && near_x < grid[near_y].size()) {
					if (grid[near_y][near_x] == actual_tag)
					{
						new_cell_in_path.first += shift_it.first;
						new_cell_in_path.second += shift_it.second;
						break;
					}
				}
			}
		}
	}
}

void Wave_Algorithm::find_exit_in_labyrinth(Labyrinth& labyrinth, std::ostream& log_stream) const
{
	//Инициализация: находим координаты героя и выхода, проверяем лабиринт на корректность
	std::vector<std::vector<std::size_t>> grid;

	fill_auxiliary_grid_with_zeros(grid, labyrinth);

	
	if (!check_labyrinth_is_correct(labyrinth))
	{
		log_stream << "Error: labyrinth is not surrounded by walls" << std::endl;
		return;
	}

	bool there_is_a_hero = false;
	bool there_is_an_exit = false;

	const auto hero_coords = find_coords_by_cell_type(labyrinth, Labyrinth::Cell_Type::HERO, there_is_a_hero);
	const auto exit_coords = find_coords_by_cell_type(labyrinth, Labyrinth::Cell_Type::EXIT, there_is_an_exit);

	if(!there_is_a_hero || !there_is_an_exit)
	{
		if (!there_is_a_hero)
		{
			log_stream << "Error: no hero found" << std::endl;
		}
		if (!there_is_an_exit)
		{
			log_stream << "Error: no exit found" << std::endl;
		}
		return;
	}

	//Распространяем волну

	const std::vector <std::pair<int, int>> dydx{ { 1, 0 } ,{ 0,  1 },
										 { -1, 0 }, { 0, -1 } };
	spread_wave(labyrinth, grid, hero_coords, exit_coords, dydx);

	//Проверяем, была ли найдена дорога. Если нет - ошибка, герой замурован
	if(grid[exit_coords.first][exit_coords.second] == 0)
	{
		log_stream << "Error: the hero is immured" << std::endl;
		return;
	}

	//Восстанавливаем путь

	std::vector<std::pair<std::size_t, std::size_t>> path;

	construct_path(labyrinth, grid, path, hero_coords, exit_coords, dydx);

	std::reverse(path.begin(), path.end()); //Разворачиваем вектор, т.к. путь записывался задом наперед
	path.pop_back(); /*Удаляем последний элемент, т.к.это сам выход.
	Мы хотим, чтобы он остался на карте лабиринта*/

	//Записываем звездочками путь в изначальном лабиринте
	for(const auto& path_iterator : path)
	{
		labyrinth.get_matrix()[path_iterator.first][path_iterator.second] = Labyrinth::Cell_Type::WAY;
	}
	log_stream << "Success: the way has been found" << std::endl;
}
