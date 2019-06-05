#include "Program.hpp"
#include "utils.hpp"
#include <stdexcept>
#include <map>
#include <algorithm>

using namespace std;

Program::Program(InstructionSet *iset)
{
	this->iset = iset;
}

Program::~Program()
{
	for (auto stmnt : statements)
		delete stmnt;
}

void Program::add(Statement *stmnt)
{
	statements.push_back(stmnt);
}

vector<string> Program::assemble()
{
	vector<string> output = vector<string>();
	map<string, string> labels = map<string, string>();
	map<string, string> equs = map<string, string>();

	// First Pass
	int addr = 0;
	for (auto s : statements)
	{
		// Label and EQU implementations
		string label = s->getLabel();
		if (label != "")
		{
			if (s->getAction() == "EQU")
			{
				equs[label] = s->getOperand();
			}
			else labels[label] = int_to_hex(addr);
		}

		// Still increment the program counter during the first pass
		// to keep label addresses accurate
		switch (s->getType())
		{
		case INS:
		case IOP:
			addr++;
			break;
		case DOP:
			string dir = s->getAction();
			if (dir == "ORG")
				addr = stoi(s->getOperand(), nullptr, 16);
			if (dir == "DC") addr++;
			else if (dir == "DS")
				addr += stoi(s->getOperand(), nullptr, 10);
			break;
		}
	}

	// Second Pass
	addr = 0;
	for (auto s : statements)
	{
		string operand = s->getOperand();
		if (operand != "")
		{
			// Handle nested EQU's
			while (equs.count(operand))
			{
				s->changeOperand(equs.at(operand));
				operand = s->getOperand();
			}

			// Handle Labels (which can't be nested)
			if (labels.count(operand))
			{
				// If it's a 12 bit address field instruction
				if (iset->find(s->getAction())->getSize() == 1)
				{
					// Use absolute addressing for the label
					s->changeOperand(labels.at(operand));
				}
				// if the address field is 8 bits
				else if (iset->find(s->getAction())->getSize() == 2)
				{
					// compute the relative address and use that
					string reladdr = int_to_hex(stoi(labels.at(operand), nullptr, 16) - addr);
					s->changeOperand(reladdr.substr(reladdr.length() - 2));
				}
				// if the address field is 4 bits
				else if (iset->find(s->getAction())->getSize() == 3)
				{
					// compute the relative address and use that
					string reladdr = int_to_hex(stoi(labels.at(operand), nullptr, 16) - addr);
					s->changeOperand(reladdr.substr(reladdr.length() - 1));
				}
			}
		}

		// Assemble the instructions and directives
		switch (s->getType())
		{
		case INS:
			// add the address and the opcode to the "machine code"
			output.push_back(int_to_hex(addr) + " : " +
				int_to_hex((int)iset->find(
					s->getAction())->getBits().to_ulong()));
			addr++;
			break;
		case IOP:
			// add the address and the disjunction of the opcode and argument
			// to the "machine code"
			output.push_back(int_to_hex(addr) + " : " +
				int_to_hex((int)iset->find(
					s->getAction())->getBits().to_ulong()
					| stoi(s->getOperand(), 0, 16)));
			addr++;
			break;
		case DOP:
			string dir = s->getAction();
			if (dir == "ORG")
			{
				// ORG changes the address to which we write
				addr = stoi(s->getOperand(), nullptr, 16);
			}
			else if (dir == "DC")
			{
				// DC adds a constant value to the memory
				output.push_back(int_to_hex(addr) + " : " +
					s->getOperand());
				addr++;
			}
			else if (dir == "DS")
			{
				// DS increments the address by the number of 
				// words we want to define as storage space
				addr += stoi(s->getOperand(), nullptr, 10);
			}
			else if (dir == "END")
			{
				// END checks to see if we have gone beyond the 
				// assigned address space for the program
				if (addr > stoi(s->getOperand(), nullptr, 16))
					throw new out_of_range(
						"Insufficient address space for the program.");
			}
			break;
		}
	}
	return output;
}
