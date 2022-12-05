#include "configfileparser.h"
#include "commandlineparser.h"
#include "excpts.h"
#include <string>


configparser::configparser(): file_begin(true) {}
configparser::configparser(const std::string& f) : file_begin(true) { open(f); }
void configparser::open(const std::string& f) {
	config.open(f);
	if (!config.is_open())
		throw file_havent_opened();
}

bool configparser::end_of_config() const {
	return config.eof();
}

const command_info& configparser::next_command(const comdata& data) {
	next();
	int counter = 0;
	command.input.resize(0);
	if (file_begin) {
		command.input.push_back(data.wav_file_path[0]);
		file_begin = false;
	}

	size_t word_begin = 0;
	std::string temp;
	for (size_t i = 0; i < buffer.size(); i++) {
		if (buffer[i] == ' ') {
			temp = buffer.substr(word_begin, i - word_begin);
			word_begin = i + 1;
			if (counter == 0) {
				command.name = temp;
				counter++;
			}
			else {
				if (temp[0] == '$') {
					command.input.push_back(data.wav_file_path[temp[1] - 1]);
				}
				else {
					int param = atoi(temp.c_str());
					command.int_param.push_back(param);
				}
			}
		}
	}
	temp = buffer.substr(word_begin, buffer.size() - word_begin);
	if (temp[0] == '$') {
		command.input.push_back(data.wav_file_path[temp[1] - 1]);
	}
	else {
		int param = atoi(temp.c_str());
		command.int_param.push_back(param);
	}



	return command;
}

inline void configparser::next() {
	buffer.resize(1);
	buffer[0] = 0;
	do{
		getline(config, buffer);
	} while (buffer[0] == '#');
}

configparser::~configparser() {
	config.close();
}
