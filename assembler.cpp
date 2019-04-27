/*-------------------------------------------------------

Minimal entry point to the program.

---------------------------------------------------------*/

#include <iostream>
#include <cstdint>
#include <bitset>
#include "utils.hpp"

int main(int argc, char *argv[])
{
    std::bitset<16> bits = 0xA;
    std::cout << bits << std::endl;

    shiftLeft(&bits);

    std::cout << bits << std::endl;
}
