#include "converter.h"
#include "audiofile.h"
#include "configfileparser.h"
#include "soundproc.h"
#include "sample.h"
#include "excpts.h"

void mix::launch(const command_info& com) {
	if (com.input.size() < 2)
		throw conv_not_enought_args(com.name.c_str());

	inaudiofile inf1(com.input[0]);
	inaudiofile inf2(com.input[1]);
	outaudiofile outf(com.output);

	std::vector<unsigned int> temp1;
	std::vector<unsigned int> temp2;
	std::vector<sample> output;

	int tick_counter = 0;
	int rate = inf1.get_sample_rate();
	int second = 0;

	while (!inf1.eof() && !inf2.eof()) {
		inf1 >> temp1;
		inf2 >> temp2;

		size_t length = std::min(temp1.size(), temp2.size());
		output.resize(length);
		for (size_t i = 0; i < length; i++) {
			if (second >= com.param[0]) {
				output[i] = (sample(temp1[i]) / sample(2)) + (sample(temp2[i]) / sample(2));
			}
			else {
				tick_counter++;
				if (tick_counter >= rate) {
					second++;
					tick_counter = 0;
				}
				output[i] = temp1[i];
			}
		}
		outf << output;
	}

	while (!inf1.eof()) {
		inf1 >> temp1;
		outf << temp1;
	}
	while (!inf2.eof()) {
		inf2 >> temp1;
		outf << temp1;
	}

}

void mix::who_am_i() {
	std::cout << "=====================================================\n";
	std::cout << "$ mix <$(extra_file)> <second> \nMix previous file from <second> with $(extra_file). \n";
	std::cout << "=====================================================\n\n";
}
