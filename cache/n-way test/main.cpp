#include <iostream>
#include <tuple>
#include <string>
#include "tupleio.h"

int main()
{
    std::tuple<std::string, int, double, char, float> test = { "HAHAHA,_The_JOKER's_TRAP", 11, -1.222, 'H', 2.87};
    std::cout << test;
}
