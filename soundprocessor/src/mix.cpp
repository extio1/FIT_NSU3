#include "converter.h"
#include "audiofile.h"
#include "configfileparser.h"
#include "sample.h"

void mix::launch(const command_info& com) {
	if (com.input.size() < 2)
		throw;

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
		if (second >= com.int_param[0]) {
			
			size_t length = std::min(temp1.size(), temp2.size());
			output.resize(length);
			for (size_t i = 0; i < length; i++) {
				output[i] = (static_cast<sample>(temp1[i]) / sample(2)) + (static_cast<sample>(temp2[i]) / sample(2));
			}

			outf << output;
		}
		else {
			inf2.skip(temp1.size());
			tick_counter += temp1.size();
			if (tick_counter >= rate) {
				second++;
				tick_counter = 0;
			}
			outf << temp1;
		}
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
	std::cout << "MIX";
}
