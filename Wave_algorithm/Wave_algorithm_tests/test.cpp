#include "pch.h"
#include "Factory.hpp"

TEST(factory_tests, simple_labyrinth) {
	std::stringstream ss_input;
	std::stringstream ss_output;
	std::stringstream log_ss;
	ss_input << "1 1 1" << std::endl;
	ss_input << "1 2 1" << std::endl;
	ss_input << "1 0 1" << std::endl;
	ss_input << "1 3 1" << std::endl;

	const Parser parser{ " " };
	Labyrinth_Factory factory{ parser };
	Wave_Algorithm algorithm;
	auto labyrinth_map = factory.create(ss_input);
	algorithm.find_exit_in_labyrinth(labyrinth_map, log_ss);
	labyrinth_map.output(ss_output);
	EXPECT_EQ("1 1 1 \n1 2 1 \n1 * 1 \n1 3 1 \n", ss_output.str());
	EXPECT_EQ("Success: the way has been found\n", log_ss.str());
}

TEST(factory_tests, broken_wall) {
	std::stringstream ss_input;
	std::stringstream ss_output;
	std::stringstream log_ss;
	ss_input << "1 0 1" << std::endl;
	ss_input << "1 2 1" << std::endl;
	ss_input << "1 0 1" << std::endl;
	ss_input << "1 3 1" << std::endl;
	ss_input << "1 1 1" << std::endl;
	const Parser parser{ " " };
	Labyrinth_Factory factory{ parser };
	Wave_Algorithm algorithm;
	auto labyrinth_map = factory.create(ss_input);
	algorithm.find_exit_in_labyrinth(labyrinth_map, log_ss);
	labyrinth_map.output(ss_output);
	EXPECT_EQ("1 0 1 \n1 2 1 \n1 0 1 \n1 3 1 \n1 1 1 \n", ss_output.str());
	EXPECT_EQ("Error: labyrinth is not surrounded by walls\n", log_ss.str());
}

TEST(factory_tests, no_hero) {
	std::stringstream ss_input;
	std::stringstream ss_output;
	std::stringstream log_ss;
	ss_input << "1 1 1" << std::endl;
	ss_input << "1 0 1" << std::endl;
	ss_input << "1 0 1" << std::endl;
	ss_input << "1 3 1" << std::endl;
	ss_input << "1 1 1" << std::endl;
	const Parser parser{ " " };
	Labyrinth_Factory factory{ parser };
	Wave_Algorithm algorithm;
	auto labyrinth_map = factory.create(ss_input);
	algorithm.find_exit_in_labyrinth(labyrinth_map, log_ss);
	labyrinth_map.output(ss_output);
	EXPECT_EQ("1 1 1 \n1 0 1 \n1 0 1 \n1 3 1 \n1 1 1 \n", ss_output.str());
	EXPECT_EQ("Error: no hero found\n", log_ss.str());
}

TEST(factory_tests, no_exit) {
	std::stringstream ss_input;
	std::stringstream ss_output;
	std::stringstream log_ss;
	ss_input << "1 1 1" << std::endl;
	ss_input << "1 2 1" << std::endl;
	ss_input << "1 0 1" << std::endl;
	ss_input << "1 0 1" << std::endl;
	ss_input << "1 1 1" << std::endl;
	const Parser parser{ " " };
	Labyrinth_Factory factory{ parser };
	Wave_Algorithm algorithm;
	auto labyrinth_map = factory.create(ss_input);
	algorithm.find_exit_in_labyrinth(labyrinth_map, log_ss);
	labyrinth_map.output(ss_output);
	EXPECT_EQ("1 1 1 \n1 2 1 \n1 0 1 \n1 0 1 \n1 1 1 \n", ss_output.str());
	EXPECT_EQ("Error: no exit found\n", log_ss.str());
}

TEST(factory_tests, immured_hero) {
	std::stringstream ss_input;
	std::stringstream ss_output;
	std::stringstream log_ss;
	ss_input << "1 1 1" << std::endl;
	ss_input << "1 2 1" << std::endl;
	ss_input << "1 1 1" << std::endl;
	ss_input << "1 3 1" << std::endl;
	ss_input << "1 1 1" << std::endl;
	const Parser parser{ " " };
	Labyrinth_Factory factory{ parser };
	Wave_Algorithm algorithm;
	auto labyrinth_map = factory.create(ss_input);
	algorithm.find_exit_in_labyrinth(labyrinth_map, log_ss);
	labyrinth_map.output(ss_output);
	EXPECT_EQ("1 1 1 \n1 2 1 \n1 1 1 \n1 3 1 \n1 1 1 \n", ss_output.str());
	EXPECT_EQ("Error: the hero is immured\n", log_ss.str());
}

TEST(factory_tests, complex_labyrinth) {
	std::stringstream ss_input;
	std::stringstream ss_output;
	std::stringstream log_ss;
	ss_input << "1 1 1 1 1 1 1 1 1 1" << std::endl;
	ss_input << "1 2 0 1 0 0 0 0 0 1" << std::endl;
	ss_input << "1 0 0 1 0 0 1 0 0 1" << std::endl;
	ss_input << "1 0 0 1 0 0 1 0 0 3" << std::endl;
	ss_input << "1 0 0 0 0 0 1 0 0 1" << std::endl;
	ss_input << "1 0 0 0 0 0 0 0 0 1" << std::endl;
	ss_input << "1 1 1 1 1 1 1 1 1 1" << std::endl;
	const Parser parser{ " " };
	Labyrinth_Factory factory{ parser };
	Wave_Algorithm algorithm;
	auto labyrinth_map = factory.create(ss_input);
	algorithm.find_exit_in_labyrinth(labyrinth_map, log_ss);
	labyrinth_map.output(ss_output);
	EXPECT_EQ("1 1 1 1 1 1 1 1 1 1 \n"
			  "1 2 * 1 0 0 0 0 0 1 \n"
			  "1 0 * 1 0 0 1 0 0 1 \n"
			  "1 0 * 1 0 0 1 0 * 3 \n"
			  "1 0 * * * * 1 0 * 1 \n"
			  "1 0 0 0 0 * * * * 1 \n"
			  "1 1 1 1 1 1 1 1 1 1 \n", ss_output.str());
	EXPECT_EQ("Success: the way has been found\n", log_ss.str());
}

