#pragma once
#include <fstream>
#include <vector>

class WavWriter {
public:
	WavWriter();
	WavWriter(int);

	void write_sample(const int, std::ofstream&);
	void write_num_b(const int, std::ofstream&, const int);

private:
	const int n_bytes_sample;
	std::vector<char> buffer;
};
