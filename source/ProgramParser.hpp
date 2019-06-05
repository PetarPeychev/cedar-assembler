#pragma once

#include <string>
#include <tuple>
#include "Program.hpp"
#include "InstructionSet.hpp"

class ProgramParser
{
private:
	std::string path;
	InstructionSet *iset;
public:
	ProgramParser(std::string, InstructionSet *);
	Program *parse();
	std::tuple<std::string, std::string, std::string> splitStatement(std::string);
};

