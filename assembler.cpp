/*-------------------------------------------------------

Minimal entry point to the program.

---------------------------------------------------------*/

#include <iostream>
#include <cstdint>
#include <bitset>
#include "utils.hpp"
#include "Instruction.hpp"
#include "InstructionSet.hpp"

int main(int argc, char *argv[])
{
    std::bitset<16> bits = 0xA;
    std::cout << bits << std::endl;

    shiftLeft(&bits);

    std::cout << bits << std::endl;

    InstructionSet instructions = InstructionSet();
    instructions.add(new Instruction("MOVEI", std::bitset<16>(0xE), 1));
    instructions.add(new Instruction("ADD", std::bitset<16>(0xD), 1));
    instructions.add(new Instruction("BNE", std::bitset<16>(0xFD), 2));
    instructions.add(new Instruction("RTS", std::bitset<16>(0x0), 0));

    std::cout << std::hex << instructions.find("MOVEI")->getBits().to_ulong() << std::endl;
    std::cout << std::hex << instructions.find("ADD")->getBits().to_ulong() << std::endl;
    std::cout << std::hex << instructions.find("BNE")->getBits().to_ulong() << std::endl;
    std::cout << std::hex << instructions.find("RTS")->getBits().to_ulong() << std::endl;
}
