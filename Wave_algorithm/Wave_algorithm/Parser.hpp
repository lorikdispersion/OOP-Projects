#pragma once

#include <vector>
#include <string>

class Parser final
{
	std::string forbidden_chars_;
public:
	Parser(const char* forbidden_chars);
	std::vector<std::string> get_parsed_string(std::istream& input) const;
};