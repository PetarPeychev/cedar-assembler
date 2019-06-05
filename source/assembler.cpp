/*-------------------------------------------------------

Entry point to the program. Handles command-line arguments
and file I/O. 

---------------------------------------------------------*/

#include <iostream>
#include <cstdint>
#include <bitset>
#include <fstream>
#include "utils.hpp"
#include "Instruction.hpp"
#include "InstructionSet.hpp"
#include "InstructionSetParser.hpp"
#include "Program.hpp"
#include "ProgramParser.hpp"
#include "Statement.hpp"

int main(int argc, char *argv[])
{
	// Parse command-line arguments
	std::string isetpath;
	std::string progpath;
	std::string outpath;
	if (argc == 4)
	{
		isetpath = argv[1];
		progpath = argv[2];
		outpath = argv[3];
	}
	else
	{
		std::cout 
			<< "Insufficient arguments provided. Please specify an instruction set, assembly program and output file names." 
			<< std::endl;
		return 1;
	}

	// Parse instruction set
	InstructionSetParser parser = InstructionSetParser(isetpath);
	InstructionSet *iset = parser.parse();

	// Parse assembly code
	ProgramParser pparser = ProgramParser(progpath, iset);
	Program *program = pparser.parse();

	// Assemble the program
	std::vector<std::string> cdm = program->assemble();

	// Write .cdm to a file
	std::ofstream output(outpath);
	for (auto line : cdm)
	{
		output << line << std::endl;
	}
	output.close();

	// Free memory
	delete program;
	delete iset;

	// Success message
	std::cout << "Assembly successful. File located at " << outpath << std::endl;
}
