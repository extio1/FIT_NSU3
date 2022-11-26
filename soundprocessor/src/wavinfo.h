#pragma once
#include <string>
#include <vector>
#include <fstream>

struct wavheader {
	char chunkId[4]; //contains "RIFF" in ascii-code
};

class wavinfo {
public:
	void read_header(std::string);
private:
	std::vector<int> data;
	std::fstream wavstream;
};
