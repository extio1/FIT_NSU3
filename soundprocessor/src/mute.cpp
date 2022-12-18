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

	unsigned int sample_rate = inf.get_sample_rate();
	start_mute = com.param[0];
	end_mute = com.param[1];
	std::vector<unsigned int> temp;

	while (!inf.eof()) {
		inf >> temp;
		convert(temp, sample_rate);
		outf << temp;
	}
}

void mute::convert(std::vector<unsigned int>& temp, unsigned int sample_rate) {
	for (unsigned int& i : temp) {
		if (tick_counter >= sample_rate) {
			time_sec += 1;
			tick_counter = 0;
		}
		if (time_sec >= start_mute && time_sec < end_mute)
			i = 0;
		tick_counter++;
	}
}

void mute::who_am_i() {
	std::cout << "=====================================================\n";
	std::cout << "$ mute <second_begin> <second_end>\nMute .wav file from <second_begin> to <second_end> second.\n";
	std::cout << "=====================================================\n";
}
