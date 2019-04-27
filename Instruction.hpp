/*-------------------------------------------------------

Represents a single instruction, read from the
instruction definition file.

---------------------------------------------------------*/

#include <string>
#include <bitset>

class Instruction
{
private:
    std::string mnemonic;
    std::bitset<16> bits;
    int size;
public:
    Instruction(std::string, std::bitset<16>, int);
    std::string getMnemonic();
    std::bitset<16> getBits();
    int getSize();
};
