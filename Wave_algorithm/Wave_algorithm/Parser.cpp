#include "Parser.hpp"

#include <istream>

Parser::Parser(const char* forbidden_chars) :
	forbidden_chars_(forbidden_chars) {}


std::vector<std::string> Parser::get_parsed_string(std::istream& input) const
{
	std::vector<std::string> vec;
	std::string string;
	std::getline(input, string);
	for (std::size_t pos = 0;;)
	{
		pos = string.find_first_not_of(forbidden_chars_, pos);
		if (pos == std::string::npos) {
			break;
		}
		const std::size_t pos1 = string.find_first_of(forbidden_chars_, pos);
		const std::size_t len = (pos1 == std::string::npos) ? std::string::npos : pos1 - pos;
		vec.push_back(string.substr(pos, len));
		if (pos1 == std::string::npos) {
			break;
		}
		pos = pos1;
	}
	return vec;
}
