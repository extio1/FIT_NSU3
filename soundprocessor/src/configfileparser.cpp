#include "configfileparser.h"
#include "commandlineparser.h"
#include "excpts.h"
#include <string>


configparser::configparser(){}
configparser::configparser(const std::string& f) { open(f); }
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

	size_t word_begin = 0;
	std::string temp;
	for (size_t i = 0; i < buffer.size(); i++) {
		if (buffer[i] == ' ') {
			word_begin = i + 1;
			temp = buffer.substr(word_begin, i);
			if (counter == 0) {
				command.name = temp;
			}
			else if (counter == 1) {
				command.output = temp;
			}
			else {
				int param = atoi(temp.c_str());
				if (param == 0 && temp.size() > 1) {
					command.input.push_back(temp);
				}
				else {
					command.int_param.push_back(param);
				}
			}
		}
	}
	return command;
}

inline void configparser::next() {
	buffer.resize(1);
	buffer[0] = 0;
	while (buffer[0] != '#') {
		getline(config, buffer);
	}
}

configparser::~configparser() {
	config.close();
}
