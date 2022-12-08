#include "converter.h"
#include "audiofile.h"
#include "configfileparser.h"
#include "excpts.h"
#include "soundproc.h"

void mute::launch(const command_info& com) {
	if(com.param.size() < 2)
		throw conv_not_enought_args(com.name.c_str());

	inaudiofile inf(com.input[0]);
	outaudiofile outf(com.output);

	unsigned int time_sec = 0;
	int sample_rate = inf.get_sample_rate();
	int tick_counter = 0;

	std::vector<unsigned int> temp;
	while (!inf.eof()) {
		inf >> temp;

		for (unsigned int& i : temp) {
			if (tick_counter >= sample_rate) {
				time_sec += 1;
				tick_counter = 0;
			}
			if (time_sec >= com.param[0] && time_sec < com.param[1])
				i = 0;
			tick_counter++;
		}

		outf << temp;
	}
}

void mute::who_am_i() {
	std::cout << "=====================================================\n";
	std::cout << "$ mute <second_begin> <second_end> \nMute .wav file from <second_begin> to <second_end> second. \n";
	std::cout << "=====================================================\n\n";
}
