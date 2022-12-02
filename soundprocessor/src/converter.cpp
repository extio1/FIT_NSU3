#include "converter.h"
#include "audiofile.h"
#include "sample.h"
#include <vector>
#include <string>
#include <string>


converter::~converter(){}

void soundproc::use(inaudiofile& inf, outaudiofile& outf, std::string& nameconv) {
	converterfabric fabric;
	if (nameconv == "copy") {
		auto conv = fabric.make_conv(nameconv);
		conv->launch(inf, outf);
	}
}


void copy::launch(inaudiofile& inf, outaudiofile& outf) {
	std::vector<int> temp;
	std::vector<sample> sampletemp;
	while (!inf.eof()) {
		inf >> temp;

		sampletemp.resize(temp.size());
		for (int i = 0; i < temp.size(); i++) {
			sampletemp[i] = temp[i];
		}
		for (int i = 0; i < temp.size(); i++) {
			temp[i] = sampletemp[i];
		}
		outf << temp;
	}
}

void copy::who_am_i() {
	std::cout << "I'm copying input .wav to output .wav. \n";
}


std::unique_ptr<converter> converterfabric::make_conv(std::string name) {
	if (name == "copy") {
		return std::make_unique<copy>();
	}
	else {
		throw;
	}
}
