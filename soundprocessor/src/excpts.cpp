#include "excpts.h"
#include <string>

const char* command_line_parser_error::what() const noexcept { return "Command line error:\n"; }
int command_line_parser_error::get_error_code() const noexcept { return error_code; }

wrong_num_arguments::wrong_num_arguments() :entered(0), mode(0) {};
wrong_num_arguments::wrong_num_arguments(int ent) :entered(ent), mode(0) {};
wrong_num_arguments::wrong_num_arguments(int ent, const char m) :entered(ent), mode(m) {};
const char* wrong_num_arguments::what() const noexcept { return "Wrong number of arguments to launch the programm.\n"; }
int wrong_num_arguments::get_error_code() const noexcept { return error_code; }
int wrong_num_arguments::how_many() const noexcept {
	return entered;
}
char wrong_num_arguments::what_for() const noexcept {
	return mode;
}

unknown_command::unknown_command() : wrong_mode(0) {}
unknown_command::unknown_command(const char m) : wrong_mode(m) {}
int unknown_command::get_error_code() const noexcept { return error_code; }
const char* unknown_command::what() const noexcept {
	return "Was entered unknown command.\n";
}
char unknown_command::what_mode() const noexcept {
	return wrong_mode;
}

wav_file_error::wav_file_error() : filename("<Not stated>") {}
wav_file_error::wav_file_error(const char* n) : filename(n) {}
int wav_file_error::get_error_code() const noexcept { return error_code; }
const char* wav_file_error::what() const noexcept {
	return "Error while opening the file \n";
}
const char* wav_file_error::what_file() const noexcept {
	return filename;
}

file_havent_opened::file_havent_opened(): name("<Not stated>") {}
file_havent_opened::file_havent_opened(const char* n): name(n) {}
const char* file_havent_opened::what_file() const noexcept { return name; }
int file_havent_opened::get_error_code() const noexcept { return error_code; }
const char* file_havent_opened::what() const noexcept {
	return "File have not opened.\n";
}

int wrong_header::get_error_code() const noexcept { return error_code; }
wrong_header::wrong_header(const char* n, const char* c): wav_file_error(n), section(c){}
wrong_header::wrong_header(): wav_file_error(), section("<Not stated>") {}
const char* wrong_header::what() const noexcept { return "Wrong wav header.\n"; }
const char* wrong_header::what_section() const noexcept { return section; }

int converter_error::get_error_code() const noexcept { return error_code; }
converter_error::converter_error() : conv_name("<Not stated>") {}
converter_error::converter_error(const char* name) : conv_name(name) {}
const char* converter_error::what() const noexcept { return "Error in converter.\n"; }
const char* converter_error::what_name() const noexcept { return conv_name; }

int conv_wrong_name::get_error_code() const noexcept { return error_code; }
conv_wrong_name::conv_wrong_name() : converter_error("<Not stated>") {}
conv_wrong_name::conv_wrong_name(const char* name) : converter_error(name) {}
const char* conv_wrong_name::what() const noexcept { return "Error while creating converter.\n"; }

int conv_not_enought_args::get_error_code() const noexcept { return error_code; }
conv_not_enought_args::conv_not_enought_args() : converter_error("<Not stated>") {}
conv_not_enought_args::conv_not_enought_args(const char* name) : converter_error(name) {}
const char* conv_not_enought_args::what() const noexcept { return "Not enougn arguments to launch the converter\n"; }
