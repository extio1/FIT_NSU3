#include <iostream>
#include <fstream>
#include <tuple>
#include <string>
#include <sstream>
#include "tupleio.h"
#include "csvparser.h"

int main()
{
    //std::tuple<std::string, int, double, char, float> test = { "HAHAHA,_The_JOKER's_TRAP", 11, -1.222, 'H', 2.87};
    //std::cout << test << '\n';
    
    std::ifstream file("test.csv");
    CsvParser<int, std::string, char, float> parser(file, 0 /*skip first lines count*/);
    /*
    int a;
    std::cin >> a;
    std::cout << '\n' << a;

   */
    parser.configure(';');
    for (std::tuple<int, std::string, char, float> rs : parser) {
        std::cout << rs << '\n';
    }

    /*std::tuple<int, int>* tu = new std::tuple<int, int>;
    std::tuple<int, int> pu = { 99, 11 };
    int* a = &std::get<0>(pu);
    *a = 1000;
    std::cout << pu;*/
    /*
    int a = 105;
    void* ptr = &a;
    int b = 12;
    int&& b1 = 13;
    int* bp = &b;
    ptr = &b1;
    std::cout << a;
    */

}
