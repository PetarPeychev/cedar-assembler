#include "Statement.hpp"

using namespace std;

Statement::Statement(SType type, string action)
{
	this->label = "";
	this->type = type;
	this->action = action;
	this->operand = "";
}

Statement::Statement(SType type, string first, string second)
{
	switch (type)
	{
	case INS:
		this->label = first;
		this->action = second;
		this->operand = "";
		break;
	case IOP:
	case DOP:
		this->label = "";
		this->action = first;
		this->operand = second;
		break;
	}
	this->type = type;
}

Statement::Statement(SType type, string label, string action, string operand)
{
	this->type = type;
	this->label = label;
	this->action = action;
	this->operand = operand;
}

SType Statement::getType()
{
	return this->type;
}

string Statement::getLabel()
{
	return this->label;
}

string Statement::getAction()
{
	return this->action;
}

string Statement::getOperand()
{
	return this->operand;
}

void Statement::changeOperand(string operand)
{
	this->operand = operand;
}
