#include "audiofile.h"
#include "convasciiint.h"
#include <fstream>
#include <iostream>
#include <string>

audiofile::audiofile(): wheader(std::make_unique<wavheader>()), wdata(std::make_unique<wavdata>()) {}

audiofile::audiofile(const char* path) : audiostr(path){
	if(audiostr.is_open()){
		wheader = std::make_unique<wavheader>(audiostr);
		wdata = std::make_unique<wavdata>(audiostr);
	}
	else {
		throw;
	}
}

void audiofile::read_header(std::string& path) {
	audiostr.open(path);
	wheader->read_header(audiostr);
}


audiofile& audiofile::operator>>(std::vector<int>& arr) {
	wdata->read(arr, audiostr);
	return *this;
}

void audiofile::create_audiofile(const char* path) {
	std::ofstream newf(path);
	if (newf.is_open()) {
		wheader->genarate_header(newf);
	}
	else {
		throw;
	}
}

audiofile::~audiofile() { audiostr.close(); }
