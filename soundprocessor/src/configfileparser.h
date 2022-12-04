#pragma once
#include <string>
#include <vector>
#include <fstream>

struct comdata;

struct command_info {
	std::string name;
	std::vector<std::string> input;
	std::string output;
	std::vector<int> int_param;
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
	std::string buffer;
	std::ifstream config;
	command_info command;
};
