
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <iomanip>

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
		default:
			return "none ";
		}
	}
	void print_winner(const std::vector<int>& score, const std::vector<strategies>& players) {
		int maxscore = 0;
		size_t winnerpos;
		for (size_t i = 0; i < score.size(); i++)
			if (score[i] > maxscore) {
				maxscore = score[i];
				winnerpos = i;
			}
		std::cout << "Winner: " << to_string(players[winnerpos]);
	}
	inline void print_players(const std::vector<strategies>& st) {
		for (auto plname : st)
			std::cout << to_string(plname);
		std::cout << '\n';
	}
}

GameState::GameState() : nSteps(0), mode('d'), score(), rules(),
configPath(), matrixFile() {};

GameState::GameState(unsigned int nstps, char md) :
	nSteps(nstps), mode(md), score() {}

GameState::GameState(unsigned int nstps, std::string cnfg, std::string mtx, char md) :
	nSteps(nstps), configPath(), matrixFile(), mode(md), score() {
	if (!cnfg.empty()) {
		//do something
	}
	if (!mtx.empty()) {
		//make other rules
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

	if (mode == 'd') {
		std::string consolein;
		std::string choice;
		int counter = 1;
		while (std::getline(std::cin, consolein), consolein != "quit") {
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
		}
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
			renew_score(arb.round());
			print_info();
		}
	}
	print_winner(score, players);
}

GameState::~GameState() {};
