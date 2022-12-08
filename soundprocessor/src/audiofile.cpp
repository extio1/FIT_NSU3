#include "audiofile.h"
#include "convasciiint.h"
#include "excpts.h"
#include "sample.h"
#include <fstream>
#include <iostream>
#include <string>

audiofile::audiofile(): wheader(std::make_unique<wavheader>()), wdata(std::make_unique<wavdata>()) {}
audiofile::~audiofile() {}

inaudiofile::inaudiofile() {};
inaudiofile::inaudiofile(const std::string& f): inaudiofile(f.c_str()) {}
inaudiofile::inaudiofile(const char* path) {
	audiostr.open(path, std::ios_base::binary);
	if (audiostr.is_open()) {
		wheader->read_header(audiostr, path);
		wdata->find_begin(audiostr, path);
	}
	else {
		throw file_havent_opened(path);
	}
}
inaudiofile& inaudiofile::operator>>(std::vector<unsigned int>& arr) {
	wdata->read(arr, audiostr);
	return *this;
}
inaudiofile& inaudiofile::operator>>(std::vector<sample>& arr) {
	std::vector<unsigned int> temp;
	wdata->read(temp, audiostr);
	arr.resize(temp.size());
	for (int i = 0; i < arr.size(); i++) {
		arr[i] = temp[i];
	}
	return *this;
}
unsigned int inaudiofile::get_sample_rate() const {
	return wheader->get_sample_rate();
}
bool inaudiofile::eof() {
	return audiostr.eof();
}
void inaudiofile::skip(int size) {
	wdata->skip(size);
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
		throw file_havent_opened(path);
	}
}
outaudiofile& outaudiofile::operator<<(std::vector<unsigned int>& arr) {
	wdata->write(arr, audiostr);
	return *this;
}
outaudiofile& outaudiofile::operator<<(std::vector<sample>& arr) {
	std::vector<unsigned int> temp(arr.size());
	for (int i = 0; i < arr.size(); i++)
		temp[i] = arr[i];

	wdata->write(temp, audiostr);
	return *this;
}
outaudiofile::~outaudiofile() { audiostr.close(); };
