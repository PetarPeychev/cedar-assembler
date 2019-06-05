#include "utils.hpp"
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

// pad on the right with 0's
void shiftLeft(std::bitset<16> *bits)
{
    while(bits->any() && !bits->test(15))
        *bits <<= 1;
}

std::string int_to_hex(int i)
{
	std::stringstream stream;
	stream
		<< setfill('0') 
		<< setw(4)
		<< uppercase
		<< hex << i;
	return stream.str();
}
