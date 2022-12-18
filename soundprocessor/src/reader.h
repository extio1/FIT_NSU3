#pragma once
#include <fstream>
#include <vector>

class WavReader {
public:
	int read_int_b(std::ifstream&, int);
private:
	std::vector<char> buffer;
};
