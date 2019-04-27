/*-------------------------------------------------------

Represents a single instruction, read from the
instruction definition file.

---------------------------------------------------------*/

#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

#include "Instruction.hpp"
#include <vector>
#include <string>

class InstructionSet
{
private:
    std::vector<Instruction *> instructions;
public:
    ~InstructionSet();
    void add(Instruction *);
    Instruction *find(std::string);
};

#endif
