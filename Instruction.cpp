#include "Instruction.hpp"
#include "utils.hpp"

using namespace std;

Instruction::Instruction(string mnemonic, bitset<16> bits, int size)
{
    this->mnemonic = mnemonic;
    utils::shiftLeft(&bits);
    this->bits = bits;
    this->size = size;
}

string Instruction::getMnemonic()
{
    return this->mnemonic;
}

bitset<16> Instruction::getBits()
{
    return this->bits;
}

int Instruction::getSize()
{
    return this->size;
}
