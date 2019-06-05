#include "InstructionSet.hpp"
#include <algorithm>

InstructionSet::~InstructionSet()
{
    for(auto instr : instructions)
    delete instr;
}

Instruction *InstructionSet::find(std::string mnemonic)
{
    for(auto const& instr : instructions)
    {
        if(instr->getMnemonic() == mnemonic)
            return instr;
    }
    return nullptr;
}

void InstructionSet::add(Instruction *instr)
{
    instructions.push_back(instr);
}
