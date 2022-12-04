#include "excpts.h"
#include <string>

namespace {
	void assign(char* to, const char* from, const int size_to, const int size_from) {
		for (int i = 0; i++; i < size_from) {
			if (i < size_to) {
				to[i] = from[i];
			}
		}
	}
}


const char* command_line_parser_error::what() const noexcept {
	return "Command line error:\n";
}
int command_line_parser_error::get_error_code() const noexcept {
	return error_code;
}


not_enough_arguments::not_enough_arguments() :entered(0), mode(0) {};
not_enough_arguments::not_enough_arguments(int ent) :entered(ent), mode(0) {};
not_enough_arguments::not_enough_arguments(int ent, const char m) :entered(ent), mode(m) {};
int not_enough_arguments::get_error_code() const noexcept { return error_code; }
const char* not_enough_arguments::what() const noexcept {
	//char* errmess = const_cast<char*>(command_line_parser_error::what());
	std::string errmess = "Not enoungh argumets.\n";
	if (mode == 'c') {
		errmess.append(std::to_string(entered));
		errmess.append(" of 3 for -c\n");
	}
	return errmess.c_str();
}

unknown_command::unknown_command() : wrong_mode(0) {}
unknown_command::unknown_command(const char m) : wrong_mode(m) {}
int unknown_command::get_error_code() const noexcept { return error_code; }
const char* unknown_command::what() const noexcept {
	std::string errmess = command_line_parser_error::what();
	errmess.append(std::to_string(wrong_mode));
	errmess.append(" is unknown. Use -h (help) or -c(config) <config.txt> <output.wav> <input.wav>... instead.\n");
	return errmess.c_str();
}

int input_wav_format_exception::get_error_code() const noexcept { return error_code; }
const char* input_wav_format_exception::what() const noexcept {
	const int messange_size = 100;
	char* error_messange = new(std::nothrow) char[messange_size];
	assign(error_messange, "Wrong wav file format\n", messange_size, 23);
	return error_messange;
}

int file_havent_opened::get_error_code() const noexcept { return error_code; }
const char* file_havent_opened::what() const noexcept {
	return "File have not opened";
}
