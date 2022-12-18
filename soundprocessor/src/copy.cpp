#include "converter.h"
#include "audiofile.h"
#include "configfileparser.h"
#include "soundproc.h"

void copy::launch(const command_info& com) {
	inaudiofile inf(com.input[0]);
	outaudiofile outf(com.output);

	std::vector<unsigned int> temp;

	while (!inf.eof()) {
		inf >> temp;
		outf << temp;
	}
}

void copy::who_am_i() {
	std::cout << "=====================================================\n";
	std::cout << "$ copy \nCopies previous file to output file. \n";
	std::cout << "=====================================================\n";
}
