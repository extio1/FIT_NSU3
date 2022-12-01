#include "audiofile.h"
#include "convasciiint.h"
#include <fstream>
#include <iostream>
#include <string>

audiofile::audiofile(): wheader(std::make_unique<wavheader>()), wdata(std::make_unique<wavdata>()) {}
audiofile::audiofile(std::fstream f){}
audiofile::~audiofile() {}
bool audiofile::eof() {
	return wdata->endof();
}

inaudiofile::inaudiofile() {};
inaudiofile::inaudiofile(const char* path) {
	audiostr.open(path, std::ios_base::binary);
	if (audiostr.is_open()) {
		wdata->find_begin(audiostr);
		wheader->read_header(audiostr);
	}
	else {
		throw;
	}
}
inaudiofile& inaudiofile::operator>>(std::vector<int>& arr) {
	wdata->read(arr, audiostr);
	return *this;
}
inaudiofile::~inaudiofile() {};


outaudiofile::outaudiofile() {};
outaudiofile::outaudiofile(const char* path) {
	audiostr.open(path, std::ios_base::binary);
	if (audiostr.is_open()) {
		wheader->genarate_header(audiostr);
	}
	else {
		throw;
	}
}
outaudiofile& outaudiofile::operator<<(std::vector<int>& arr) {
	wdata->write(arr, audiostr);
	return *this;
}
outaudiofile::~outaudiofile() {};
