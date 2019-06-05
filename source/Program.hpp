#pragma once

#include <vector>
#include <string>
#include "Statement.hpp"
#include "InstructionSet.hpp"

class Program
{
private:
	std::vector<Statement *> statements;
	InstructionSet *iset;
public:
	Program(InstructionSet *);
	~Program();
	void add(Statement *);
	std::vector<std::string> assemble();
};

