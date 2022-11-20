#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "gamestate.h"
#include "arbitrator.h"
#include "strategies.h"
#include "strenumconv.h"

namespace {
	inline void print_players(const std::vector<strategies>& st) {
		for (auto plname : st)
			std::cout << to_string(plname);
		std::cout << '\n';
	}
	bool check_key(std::string& key) {
		for (size_t i = 0; i < key.size(); i++) {
			if (i > 3 || (key[i] != 'D' && key[i] != 'C'))
				return false;
		}
		return true;
	}
	bool check_value(std::string& value) {
		for (size_t i = 0; i < value.size(); i++) {
			if (i > 3 || !('0' < value[i] && value[i] < '9'))
				return false;
		}
		return true;
	}
}
void assign_matrix(std::string mtx, GameState& game) {
	std::ifstream in(mtx);

	std::map<std::string, std::string> read;
	std::string key;
	std::string value;
	if (in.is_open()) {
		while (!in.eof() && !in.fail()) {
			getline(in, key, ';');
			getline(in, value, ';');
			if (check_key(key) && check_value(value))
				read[key] = value;
			else
				in.clear(std::ifstream::failbit);
		}
		if (!in.fail() && !in.bad()) {
			game.rules = read;
		}
		else if (in.fail()) {
			throw(1);
		}
		else {
			throw(2);
		}
	}
	else {
		throw(3);
	}
	in.close();
}

GameState::GameState() {
	rules = { {"CCC", "777"}, {"CCD", "339"}, {"CDC", "393"}, {"DCC", "933"},
					{"CDD", "055"}, {"DCD", "505"}, {"DDC", "550"}, {"DDD", "111"} };
}
GameState::GameState(std::string mtx, std::string cnfg) {
	if (!cnfg.empty()) {
		configPath = cnfg;
	}
	if (!mtx.empty()) {
		try {
			assign_matrix(mtx, *this);
		}
		catch(int errornum){
			switch (errornum) {
			case 1:
				std::cerr << "Input file values are wrong\n";
				exit(1);
			case 2:
				std::cerr << "Error while reading the file\n";
				exit(2);
			case 3:
				std::cerr << "Matrix file haven't read\n";
				exit(3);
			}
		}
	}
	else {
		*this = GameState();
	}
}

const std::map<std::string, std::string>& GameState::get_rules() const { return rules; }

void GameState::start(const std::vector<strategies>& players, const int nSteps, const char mode) { 
	arbitrator arb(*this);
	try {
		arb.create_players(players);
	}
	catch (int err) {
		if (err == 1) {
			std::cerr << "Error while creating the player\n";
			exit(1);
		}
	}

	std::string choice;
	if (mode == 'd') {
		std::string consolein;
		int counter = 1;
		do {
			arb.match();
			std::cout << "=================================\n";
			std::cout << "Round #" << counter << ":\n";
			print_players(players);
			std::cout << "Choice : ";
			arb.show_choice();
			std::cout << "Score for this round : ";
			arb.show_score_round();
			std::cout << "\nScore for the game : ";
			arb.show_score_game();
			std::cout << "=================================\n";
			counter++;
		} while ((std::getline(std::cin, consolein), consolein != "quit"));
	}
	else if (mode == 'f') {
		for (size_t i = 0; i < nSteps; i++)
			arb.match();
		print_players(players);
		arb.show_score_game();
	}
	else {
		arb.tournament(nSteps);
		print_players(players);
		arb.show_score_game();
	}
	std::cout << "Winner: " << to_string(players[arb.who_winner()]);
}

GameState::~GameState() {};
