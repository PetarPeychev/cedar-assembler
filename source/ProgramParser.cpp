#include "ProgramParser.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

ProgramParser::ProgramParser(string path, InstructionSet *iset)
{
	this->path = path;
	this->iset = iset;
}

Program *ProgramParser::parse()
{
	// attempt to open the file
	ifstream file(path);
	if (file.is_open())
	{
		Program *program = new Program(iset);

		// read a line
		string line;
		while (getline(file, line))
		{
			// transform to uppercase to be case-insensitive
			transform(line.begin(), line.end(), line.begin(), ::toupper);

			// split by whitespace into 1, 2 or 3 strings
			auto tup = splitStatement(line);
			string first = get<0>(tup);
			string second = get<1>(tup);
			string third = get<2>(tup);

			// if there's only one then the line is an instruction with no operand
			if (first != "" && second == "")
			{
				program->add(new Statement(INS, first));
			}
			else if (first != "" && second != "" && third == "")
			{
				// If there's two strings, it's 
				// either instruction with operand 
				// or labeled instruction with no operand
				// or directive with operand
				// to check, see if the first string is an instruction mnemonic
				// then see if the second string is an instruction mnemonic
				Instruction *inst = iset->find(first);
				Instruction *inst2 = iset->find(second);
				if (inst)
				{
					// it's an instruction with an operand
					program->add(new Statement(IOP, first, second));
				}
				else if (inst2)
				{
					// labeled instruction with no operand
					program->add(new Statement(INS, first, second));
				}
				else
				{
					// directive with operand
					program->add(new Statement(DOP, first, second));
				}
			}
			else if (first != "" && second != "" && third != "")
			{
				// it's either a labeled directive with an operand
				// or a labeled instruction with an operand
				// to check, see if the second string is an instruction mnemonic
				Instruction *inst = iset->find(second);
				if (inst)
				{
					// it's a labeled instruction with an operand
					program->add(new Statement(IOP, first, second, third));
				}
				else
				{
					// it's a labeled directive with no operand
					program->add(new Statement(DOP, first, second, third));
				}
			}
		}
		file.close();
		return program;
	}
	else
	{
		return nullptr;
	}
}

// split by whitespace into 1, 2 or 3 strings
tuple<string, string, string> ProgramParser::splitStatement(string s)
{
	string first = "";
	string second = "";
	string third = "";
	string delimiters = " \t";
	size_t current;
	size_t next = -1;
	do
	{
		current = next + 1;
		next = s.find_first_of(delimiters, current);
		string substr = s.substr(current, next - current);
		if (substr != "")
		{
			if (first == "") first = substr;
			else if (second == "") second = substr;
			else if (third == "") third = substr;
		}
	} while (next != string::npos);
	return tuple<string, string, string>(first, second, third);
}
