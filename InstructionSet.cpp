#include "InstructionSet.hpp"
#include <algorithm>

Instruction *InstructionSet::find(std::string mnemonic)
{
    for(auto const& instr : instructions)
    {
        if(instr->getMnemonic() == mnemonic)
            return instr;
    }
    return NULL;
}

void InstructionSet::add(Instruction *instr)
{
    instructions.push_back(instr);
}

InstructionSet::~InstructionSet()
{
    for(auto instr : instructions)
        delete instr;
}
