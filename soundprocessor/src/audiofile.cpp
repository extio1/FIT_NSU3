#include "audiofile.h"
#include "convasciiint.h"
#include "excpts.h"
#include <fstream>
#include <iostream>
#include <string>

audiofile::audiofile(): wheader(std::make_unique<wavheader>()), wdata(std::make_unique<wavdata>()) {}
//audiofile::audiofile(std::fstream f){}
audiofile::~audiofile() {}
bool audiofile::eof() {
	return wdata->endof();
}

inaudiofile::inaudiofile() {};
inaudiofile::inaudiofile(const std::string& f): inaudiofile(f.c_str()) {}
inaudiofile::inaudiofile(const char* path) {
	audiostr.open(path, std::ios_base::binary);
	if (audiostr.is_open()) {
		wheader->read_header(audiostr);
		wdata->find_begin(audiostr);
	}
	else {
		throw file_havent_opened();
	}
}
inaudiofile& inaudiofile::operator>>(std::vector<int>& arr) {
	wdata->read(arr, audiostr);
	return *this;
}
inaudiofile::~inaudiofile() { audiostr.close(); };


outaudiofile::outaudiofile() {};
outaudiofile::outaudiofile(const std::string& f) : outaudiofile(f.c_str()) {}
outaudiofile::outaudiofile(const char* path) {
	audiostr.open(path, std::ios_base::binary);
	if (audiostr.is_open()) {
		wheader->genarate_header(audiostr);
	}
	else {
		throw file_havent_opened();
	}
}
outaudiofile& outaudiofile::operator<<(std::vector<int>& arr) {
	wdata->write(arr, audiostr);
	return *this;
}
outaudiofile::~outaudiofile() { audiostr.close(); };
