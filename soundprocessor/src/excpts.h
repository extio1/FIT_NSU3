#pragma once
#include <iostream>

class command_line_parser_error : public std::exception { //ошибка парсера - общее
public:
	virtual const char* what() const noexcept override;
	virtual int get_error_code() const noexcept;
private:
	static const int error_code = 10;
};

class wrong_num_arguments : public command_line_parser_error { //ошибка парсера - некорректный набор параметров
public:
	wrong_num_arguments();
	wrong_num_arguments(int);
	wrong_num_arguments(int, const char);
	const char* what() const noexcept;
	int how_many() const noexcept;
	char what_for() const noexcept;
	int get_error_code() const noexcept;
private:
	static const int error_code = 11;
	int entered;
	char mode;
};

class unknown_command : public command_line_parser_error { //ошибка парсера - неизвезстый режим работы (не -c или -h)
public:
	unknown_command();
	unknown_command(const char);
	const char* what() const noexcept;
	char what_mode() const noexcept;
	int get_error_code() const noexcept;
private:
	static const int error_code = 12;
	char wrong_mode;
};

class wav_file_error : public std::exception { //общая ошибка связанная с wav файлом
public:
	wav_file_error();
	wav_file_error(const char*);
	const char* what() const noexcept override;
	const char* what_file() const noexcept;
	virtual int get_error_code() const noexcept;
protected:
	const char* filename;
private:
	static const int error_code = 20;
};

class wrong_header : public wav_file_error { //неправильная wav заговочная часть
public:
	wrong_header();
	wrong_header(const char*, const char*);
	using wav_file_error::what_file;
	const char* what() const noexcept override;
	const char* what_section() const noexcept;
	int get_error_code() const noexcept override;
private:
	const char* section;
	static const int error_code = 21;
};

class file_havent_opened : public std::exception { //файл не был открыл
public:
	file_havent_opened();
	file_havent_opened(const char*);
	const char* what() const noexcept override;
	const char* what_file() const noexcept;
	int get_error_code() const noexcept;
private:
	const char* name;
	static const int error_code = 30;
};

class converter_error : public std::exception {
public:
	converter_error();
	converter_error(const char*);
	const char* what() const noexcept override;
	const char* what_name() const noexcept;
	int get_error_code() const noexcept;
protected:
	const char* conv_name;
private:
	static const int error_code = 40;
};

class conv_wrong_name : public converter_error {
public:
	conv_wrong_name();
	conv_wrong_name(const char*);
	using converter_error::what_name;
	const char* what() const noexcept override;
	int get_error_code() const noexcept;
private:
	static const int error_code = 41;
};

class conv_not_enought_args : public converter_error {
public:
	conv_not_enought_args();
	conv_not_enought_args(const char*);
	using converter_error::what_name;
	const char* what() const noexcept override;
	int get_error_code() const noexcept;
private:
	static const int error_code = 42;
};
