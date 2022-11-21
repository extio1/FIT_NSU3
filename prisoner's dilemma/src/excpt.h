#pragma once
#include <iostream>
#include <string>

enum class strategies;

class invalid_command : public std::exception {
public:
	invalid_command();
	invalid_command(std::string);
	const char* what() const noexcept override;
private:
	std::string wrong_command;
};

class invalid_player : public std::exception {
public:
	invalid_player();
	invalid_player(std::string);
	invalid_player(strategies);
	const char* what() const noexcept override;
private:
	std::string player_name;
};

class not_enough_players : public std::exception {
public:
	not_enough_players();
	not_enough_players(int);
	int how_many() const noexcept;
private:
	int num_of_plrs;
};
