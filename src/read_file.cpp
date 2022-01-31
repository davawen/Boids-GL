#include "read_file.hpp"

std::string read_file(const std::string &filename)
{
	std::fstream file(filename);
	if(!file.is_open()) throw std::runtime_error("Couldn't open file \"" + filename + "\"\n");

	std::string line;
	std::string output;

	while(std::getline(file, line))
	{
		output += line;
		output += "\n";
	}

	return output;
}
