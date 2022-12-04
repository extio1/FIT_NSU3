#pragma once
#include <iostream>

class command_line_parser_error : public std::exception {
public:
	virtual const char* what() const noexcept override;
	virtual int get_error_code() const noexcept;
private:
	static const int error_code = 10;
};

class not_enough_arguments : public command_line_parser_error {
public:
	not_enough_arguments();
	not_enough_arguments(int);
	not_enough_arguments(int, const char);
	const char* what() const noexcept final;
	int get_error_code() const noexcept;
private:
	static const int error_code = 11;
	int entered;
	char mode;
};

class unknown_command : public command_line_parser_error {
public:
	unknown_command();
	unknown_command(const char);
	const char* what() const noexcept final;
	int get_error_code() const noexcept;
private:
	static const int error_code = 12;
	char wrong_mode;
};

class input_wav_format_exception : public std::exception {
public:
	virtual const char* what() const noexcept override;
	virtual int get_error_code() const noexcept;
private:
	static const int error_code = 20;
};
/*
class wrong_header : public input_wav_format_exception {
public:
	const char* what() const noexcept override;
	int get_error_code() const noexcept override;
private:
	static const int error_code = 21;
};
*/

class file_havent_opened : public std::exception {
public:
	const char* what() const noexcept override;
	int get_error_code() const noexcept;
private:
	static const int error_code = 30;
};
