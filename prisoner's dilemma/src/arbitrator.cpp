#include "arbitrator.h"
#include "strategies.h"
#include "gamestate.h"
#include <iostream>
#include <map>

namespace{
	std::vector<int> calc_score_by_choice(const std::vector<char>& choice, const std::map<std::string, std::string>& rules) {
		const int ASCII_TO_INT = 48;

		std::vector<int> score(3);
		char versC[4] = { choice[0], choice[1], choice[2], '\0' };
		std::string vers(versC);
		std::string score_rul = rules.at(vers);

		score[0] = score_rul[0] - ASCII_TO_INT;
		score[1] = score_rul[1] - ASCII_TO_INT;
		score[2] = score_rul[2] - ASCII_TO_INT;

		return score;
	}
}

void arbitrator::show_score_game() const {
	for (int i : scoregame)
		std::cout << i << ' ';
	std::cout << std::endl;
}
void arbitrator::show_score_round() const {
	for (int i : scoreround)
		std::cout << i << ' ';
	std::cout << std::endl;
}
void arbitrator::show_choice() const {
	for (char i : choice)
		std::cout << i << ' ';
	std::cout << std::endl;
}
size_t arbitrator::who_winner() const {
	size_t pos = 0;
	int max = 0;
	for (size_t i = 0; i < scoregame.size(); i++) {
		if (scoregame[i] > max) {
			max = scoregame[i];
			pos = i;
		}
	}
	return pos;
}

void arbitrator::match() {
	std::vector<char> roundChoice(3);
	for (int i = 0; i < 3; i++)
		roundChoice[i] = players[i]->make_step();

	std::vector<int> roundScore = calc_score_by_choice(roundChoice, game.get_rules());
	for (int i = 0; i < 3; i++)
		scoregame[i] += roundScore[i];
	choice = roundChoice;
	scoreround = roundScore;

	for (int i = 0; i < 3; i++) { //всем игрокам передали информацию об их опонентах и изменили счет за раунд
		players[i]->enter_choice(std::vector<char>{roundChoice[(i + 1) % 3], roundChoice[(i + 2) % 3]});
		players[i]->enter_score(std::vector<int>{roundScore[(i + 1) % 3], roundScore[(i + 2) % 3]});
	}
}

void arbitrator::match(const size_t pl1, const size_t pl2, const size_t pl3, const int nsteps) { //под раундом подразумевается
	std::vector<char> roundChoice(3);                                                   //nsores игр pl1, pl2, pl3
	std::vector<size_t> currplayers{ pl1, pl2, pl3 };										//против друг друга
	int n = players.size();

	for (int k = 0; k < nsteps; k++) {
		for (int i = 0; i < 3; i++)
			roundChoice[i] = players[currplayers[i]]->make_step();

		std::vector<int> roundScore = calc_score_by_choice(roundChoice, game.get_rules());

		for (int i = 0; i < 3; i++) { 
			players[currplayers[i]]->enter_choice(std::vector<char>{roundChoice[(i + 1) % 3], roundChoice[(i + 2) % 3]});
			players[currplayers[i]]->enter_score(std::vector<int>{roundScore[(i + 1) % 3], roundScore[(i + 2) % 3]});
			scoreround[i] += roundScore[i];
		}
	}

	std::cout << pl1 << ' ' << pl2 << ' ' << pl3 << '\n';
	for (int i = 0; i < 3; i++) {
		std::cout << scoreround[i] << ' ';
	}
	std::cout << "\n\n";

	for (int i = 0; i < 3; i++) { //изменили общий счет игры и затерли всю информацию у игроков про этот раунд
		scoregame[currplayers[i]] += scoreround[i];
		players[currplayers[i]]->clear();
		scoreround[i] = 0;
	}
}

void arbitrator::tournament(const int nsteps) {
	size_t nPlayers = players.size();
	for (size_t i = 0; i < nPlayers; i++) {
		for (size_t j = i+1; j < nPlayers; j++) {
			for (size_t k = j+1; k < nPlayers; k++) {
				match(i, j, k, nsteps);
			}
		}
	}
}

void arbitrator::create_players(const std::vector<strategies>& strategs) {
	PlayerFabric fabric;
	players.reserve(strategs.size());
	scoregame.resize(strategs.size());
	for (strategies s : strategs) {
		players.push_back(fabric.make_player(s));
	}
}

arbitrator::arbitrator(GameState& gm): game(gm), scoregame(3), scoreround(3), choice(3) {}
arbitrator::~arbitrator(){}
