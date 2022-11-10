#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "gamestate.h"
#include "arbitrator.h"
#include "strategies.h"

namespace {
	std::string to_string(strategies st) {
		switch (st) {
		case(strategies::allcooperate):
			return "allcooperate ";
		case(strategies::alldefect):
			return "alldefect ";
		case(strategies::titfortat):
			return "titfortat ";
		case(strategies::grim):
			return "grim ";
		default:
			return "none ";
		}
	}
	void print_winner(const std::vector<int>& score, const std::vector<strategies>& players) {
		int maxscore = 0;
		size_t winnerpos = 0;
		std::cout << "Winner: ";
		for (size_t i = 0; i < score.size(); i++)
			if (score[i] >= maxscore) {
				maxscore = score[i];
				winnerpos = i;
			}
		std::cout << to_string(players[winnerpos]);
	}
	inline void print_players(const std::vector<strategies>& st) {
		for (auto plname : st)
			std::cout << to_string(plname);
		std::cout << '\n';
	}
	strategies str_to_enum(char* s) {
		std::string str(s);
		if (str == "alldefect")
			return strategies::alldefect;
		else if (str == "allcooperate")
			return strategies::allcooperate;
		else if (str == "grim")
			return strategies::grim;
		else if (str == "titfortat")
			return strategies::titfortat;
	}
	void parse(int argc, char** argv, char* mode, int* steps, std::string* cnfgs, std::string* mtrx, std::vector<strategies>* strats) {
		size_t i = 1;
		for (i; i < argc && argv[i][0] != '-'; i++) //reading only strategies
			strats->push_back(str_to_enum(argv[i]));
		if (i < 3) {
			std::cout << "There is not enough participants\n";
			exit(1);
		}

		for (i; i < argc; i++) {
			if (argv[i][0] == '-' && argv[i][1] == '-') {
				std::string option;
				std::string value;
				size_t j = 2;
				for (j; argv[i][j] != '='; j++)
					option.push_back(argv[i][j]);
				j++;
				for (j; j < std::string(argv[i]).size(); j++)
					value.push_back(argv[i][j]);
				
				if (option == "mode")
					*mode = value[0];
				else if (option == "steps")
					*steps = atoi(value.c_str());
				else if (option == "matrix")
					*mtrx = value;
				else if (option == "config")
					*cnfgs = value;
				else {
					std::cout << "Unknown command";
					exit(0);
				}

			}
		}
	}
	bool check_key(std::string& key) {
		for (int i = 0; i < key.size(); i++) {
			if (i > 3 || (key[i] != 'D' && key[i] != 'C'))
				return false;
		}
		return true;
	}
	bool check_value(std::string& value) {
		for (int i = 0; i < value.size(); i++) {
			if (i > 3 || !('0' < value[i] < '9'))
				return false;
		}
		return true;
	}
}

GameState::GameState() : nSteps(0), mode('d') {};
GameState::GameState(int argc, char** argv){
	std::vector<strategies> strats;
	strats.reserve(3);
	char mode = 'd';
	int steps = -1;
	std::string configPath;
	std::string matrixPath;
	parse(argc, argv, &mode, &steps, &configPath, &matrixPath, &strats);
	if (steps == -1 && strats.size() > 3)
		mode = 't';
	//std::cout << mode << ' ' << steps << ' ' << matrixPath << ' ' << configPath;
	GameState dilemma(steps, configPath, matrixPath, mode);
}

GameState::GameState(int nstps, std::string cnfg, std::string mtx, char md) :
	nSteps(nstps), configPath(cnfg), mode(md) {
	if (!cnfg.empty()) {
		configPath = cnfg;
	}
	if (!mtx.empty()) {
		std::ifstream in(mtx);
		
		std::map<std::string, std::string> read;
		std::string key;
		std::string value;
		if (in.is_open()) {
			while (!in.eof()) {
				getline(in, key, ';');
				getline(in, value, ';');
				if (check_key(key) && check_value(value))
					read[key] = value;
				else
					in.clear(std::ifstream::failbit);
			}
			if (!in.fail() && !in.bad()) {
				rules = read;
			}
			else if (in.fail()) {
				std::cerr << "Input file values are wrong\n";
				exit(0);
			}
			else {
				std::cerr << "Error while reading the file\n";
				exit(0);
			}
		}
		else {
			std::cerr << "Matrix file haven't read\n";
			exit(0);
		}
		in.close();
	}
	else {
		rules = { {"CCC", "777"}, {"CCD", "339"}, {"CDC", "393"}, {"DCC", "933"},
					{"CDD", "055"}, {"DCD", "505"}, {"DDC", "550"}, {"DDD", "111"} };
	}
}

void GameState::print_info() const {
	for (int i : score)
		std::cout << i << ' ';

	std::cout << '\n';
}

void GameState::renew_score(const std::vector<int>& newScore) {;
	for (int i = 0; i < score.size(); i++)
		score[i] += newScore[i];
}

const std::vector<int>& GameState::get_info() const { return score; }
const std::map<std::string, std::string>& GameState::get_rules() const { return rules; }

void GameState::start(const std::vector<strategies>& players, const char mode) {
	arbitrator arb(*this);
	score.resize(players.size());
	arb.create_players(players);

	std::string choice;
	if (mode == 'd') {
		std::string consolein;
		int counter = 1;
		do {
			std::vector<int> scoreRound = arb.round(&choice);
			renew_score(scoreRound);
			std::cout << "=================================\n";
			std::cout << "Round #" << counter << ":\n";
			print_players(players);
			std::cout << "Choice : ";
			std::cout << choice << '\n';
			std::cout << "Score for this round : ";
			for (int el : scoreRound)
				std::cout << el << ' ';
			std::cout << "\nScore for the game : ";
			print_info();
			std::cout << "=================================\n";
			counter++;
		} while ((std::getline(std::cin, consolein), consolein != "quit"));
	}
	else if (mode == 'f') {
		for (size_t i = 0; i < nSteps; i++)
			renew_score(arb.round());
		print_players(players);
		print_info();
	}
	else {
		print_players(players);
		for (size_t i = 0; i < nSteps; i++) {
			renew_score(arb.round(&choice));
			print_info();
			std::cout << choice << '\n';
		}
	}
	print_winner(score, players);
}

GameState::~GameState() {};
