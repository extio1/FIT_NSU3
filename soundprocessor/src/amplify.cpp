#include "converter.h"
#include "audiofile.h"
#include "sample.h"
#include "configfileparser.h"
#include "excpts.h"
#include "soundproc.h"

void amplify::launch(const command_info& com) {
	if (com.param.size() < 1)
		throw conv_not_enought_args(com.name.c_str());

	inaudiofile inf(com.input[0]);
	outaudiofile outf(com.output);

	float param = com.param[0];

	std::vector<sample> temp;

	while (!inf.eof()) {
		inf >> temp;
		for (sample& i : temp) {
			i *= param;
		}
		outf << temp;
	}
}

void amplify::who_am_i() {
	std::cout << "=====================================================\n";
	std::cout << "$ amplify <paramenter> \nChange volume in <paramenter> times. \n";
	std::cout << "=====================================================\n\n";
}
