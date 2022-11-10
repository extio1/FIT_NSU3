#include "arbitrator.h"
#include "strategies.h"
#include "gamestate.h"
#include <iostream>
std::vector<int> arbitrator::round(std::string* choice) {
	size_t nPlayers = players.size();
	std::vector<char> roundChoice(nPlayers);
	std::vector<int> roundScore(nPlayers); //vector stored by zeros automatically.
	size_t i = 0;
	for (auto player : players)
		roundChoice[i++] = player->make_step();

	const int ASCII_TO_INT = 48;
	for (size_t i = 0; i < nPlayers; i++) {
		for (size_t j = i+ 1; j < nPlayers; j++) {
			for (size_t k = j + 1; k < nPlayers; k++) {

				//std::cout << i << ' ' << j << ' ' << k << std::endl;

				char versC[4] = { roundChoice[i], roundChoice[j], roundChoice[k], '\0'};
				std::string vers(versC);

				//std::cout << vers << '\n';

				if(choice != nullptr) (*choice) = vers;
				decltype(auto) rules = const_cast<std::map<std::string, std::string>&>(game.get_rules());
				std::string score = rules[vers];
				roundScore[i] += score[0] - ASCII_TO_INT;
				roundScore[j] += score[1] - ASCII_TO_INT;
				roundScore[k] += score[2] - ASCII_TO_INT;
			}
		}
	}

	for (auto player : players) {
		player->enter_choice(roundChoice);
		player->enter_score(roundScore);
	}

	return roundScore;
}

void arbitrator::create_players(const std::vector<strategies>& strategs) {
	PlayerFabric fabric;
	players.reserve(strategs.size());
	for (strategies s : strategs)
		players.push_back(fabric.make_player(s));
}

arbitrator::arbitrator(GameState& gm): game(gm) {}
arbitrator::~arbitrator(){}
