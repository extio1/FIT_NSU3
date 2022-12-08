#include "configfileparser.h"
#include "commandlineparser.h"
#include "excpts.h"
#include <string>


configparser::configparser() : file_begin(true), command_counter(1) {}
configparser::configparser(const std::string& f) : file_begin(true), command_counter(1) { open(f); }
void configparser::open(const std::string& f) {
	config.open(f);
	if (!config.is_open())
		throw file_havent_opened(f.c_str());
}

bool configparser::end_of_config() const {
	return config.eof();
}

const command_info& configparser::next_command(const comdata& data) {
	next();
	new_command();
	
	if (file_begin) {
		command.input.push_back(data.input_path[0]);
		file_begin = false;
		output = "output1.wav";
		command.output = output;
	}
	else {
		command.input.push_back(output);
		if (command_counter % 2) {
			output = "output2.wav";
			command.output = output;
		}
		else {
			output = "output1.wav";
			command.output = output;
		}
		command_counter++;
	}

	int counter = 0;
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
					command.input.push_back(data.input_path[1ll * temp[1] - ASCII_TO_INT]);
				}
				else {
					float param = atof(temp.c_str());
					command.param.push_back(param);
				}
			}
		}
	}

	temp = buffer.substr(word_begin, buffer.size() - word_begin);
	if (command.name == "") {
		command.name = temp;
	}
	else if (temp[0] == '$') {
		command.input.push_back(data.input_path[1ll * temp[1] - ASCII_TO_INT]);
	}
	else {
		float param = atof(temp.c_str());
		command.param.push_back(param);
	}

	return command;
}

inline void configparser::next() {
	buffer.resize(1);
	buffer[0] = 0;
	do {
		getline(config, buffer);
	} while (buffer[0] == '#');
}


inline void configparser::new_command() {
	command.name.resize(0);
	command.input.resize(0);
	command.output.resize(0);
	command.param.resize(0);
}


configparser::~configparser() {
	config.close();
}
