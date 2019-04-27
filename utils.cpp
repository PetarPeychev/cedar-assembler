#include "utils.hpp"

using namespace std;

void shiftLeft(std::bitset<16> *bits)
{
    while(!bits->test(15))
        *bits <<= 1;
}
