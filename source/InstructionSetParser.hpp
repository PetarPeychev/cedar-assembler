#pragma once

#include <string>
#include "InstructionSet.hpp"

class InstructionSetParser
{
private:
	std::string path;
public:
	InstructionSetParser(std::string);
	InstructionSet *parse();
};

