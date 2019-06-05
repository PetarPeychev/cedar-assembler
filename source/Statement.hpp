#pragma once

#include <string>

enum SType
{
	INS,	// instruction without operand
	IOP,	// instruction with operand
	DOP		// directive with operand
};

class Statement
{
private:
	SType type;
	std::string label;
	std::string action;
	std::string operand;
public:
	Statement(SType, std::string, std::string, std::string);
	Statement(SType, std::string, std::string);
	Statement(SType, std::string);
	SType getType();
	std::string getLabel();
	std::string getAction();
	std::string getOperand();
	void changeOperand(std::string);
};

