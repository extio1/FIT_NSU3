#pragma once
#include <string>
#include <vector>
#include <fstream>

struct comdata;

struct command_info {
	std::string name;
	std::vector<std::string> input;
	std::string output;
	std::vector<float> param;
};

class configparser {
public:
	configparser();
	configparser(const std::string&);
	void open(const std::string&);
	const command_info& next_command(const comdata&);
	bool end_of_config() const;
	~configparser();
private:
	inline void next();
	inline void new_command();

	int command_counter;
	bool file_begin;
	std::string buffer;
	std::string output;
	std::ifstream config;
	command_info command;
	static const int ASCII_TO_INT = 48;
};
