#include "converter.h"
#include "audiofile.h"
#include "sample.h"
#include "configfileparser.h"
#include <vector>
#include <string>
#include <string>


converter::~converter(){}

void soundproc::use(const command_info& com) const {
	converterfabric fabric;

	auto conv = fabric.make_conv(com.name);
	conv->launch(com);
}


void copy::launch(const command_info& com) {
	std::vector<int> temp;

	inaudiofile inf(com.input[0]);
	outaudiofile outf(com.output);

	while (!inf.eof()) {
		inf >> temp;
		outf << temp;
	}
}

void copy::who_am_i() {
	std::cout << "copy <infile> \nCopy <infile> to output.wav. \n";
}

mute::mute(){}
//mute::mute(unsigned int b, unsigned int e): begin(b), end(e+5) {}

void mute::launch(const command_info& com) {
	inaudiofile inf(com.input[0]);
	outaudiofile outf(com.output);

	unsigned int time_sec = 0;
	int sample_rate = inf.wheader->get_sample_rate();
	int tick_counter = 0;

	std::vector<int> temp;
	while (!inf.eof()) {
		inf >> temp;
		
		for (int& i : temp) {
			if (tick_counter >= sample_rate) {
				time_sec += 1;
				tick_counter = 0;
			}

			if (time_sec >= com.int_param[0] && time_sec < com.int_param[1])
				i = 0;

			tick_counter++;
		}

		outf << temp;
	}
}

void mute::who_am_i() {
	std::cout << "mute <A> <B> \nMute .wav file from <A> to <B> seconds \n";
}


std::unique_ptr<converter> converterfabric::make_conv(std::string name) {
	if (name == "copy") {
		return std::make_unique<copy>();
	}
	else if (name == "mute") {
		return std::make_unique<mute>();
	}
	else {
		throw;
	}
}
