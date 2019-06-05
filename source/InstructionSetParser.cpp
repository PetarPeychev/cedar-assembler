#include "InstructionSetParser.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

InstructionSetParser::InstructionSetParser(string path)
{
	this->path = path;
}

InstructionSet *InstructionSetParser::parse()
{
	// Attempt to open the file
	ifstream file(path);
	if (file.is_open())
	{
		InstructionSet *instructions = new InstructionSet();

		// Read a line
		string line;
		while (getline(file, line))
		{
			// Transform to uppercase to be case-insensitive
			transform(line.begin(), line.end(), line.begin(), ::toupper);

			// Read the first word as a mnemonic
			string mnemonic = "";
			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] == ' ' || line[i] == ':' || line[i] == '\t')
				{
					line = line.substr(
						line.find(mnemonic) + mnemonic.length(), 
						line.length() - mnemonic.length());
					break;
				}
				mnemonic += line[i];
			}

			// Read the second word as an opcode
			string sopcode = "";
			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] != ' ' && line[i] != ':' && line[i] != '\t')
				{
					sopcode += line[i];
				}
			}
			int size = sopcode.length();
			int opcode = stoi(sopcode, 0, 16);

			// Push an instruction pointer to the set 
			instructions->add(new Instruction(mnemonic, std::bitset<16>(opcode), size));
		}

		file.close();
		return instructions;
	}
	else
	{
		return nullptr;
	}
}


