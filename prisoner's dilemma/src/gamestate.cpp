#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "gamestate.h"
#include "arbitrator.h"
#include "strategies.h"

GameState::GameState() : nSteps(0), mode('d'), condition(), rules(),
		configPath(), matrixFile() {};

GameState::GameState(unsigned int nstps, char md) :
		nSteps(nstps), mode(md), condition() {}

GameState::GameState(unsigned int nstps, std::string cnfg, std::string mtx, char md) :
	nSteps(nstps), configPath(), matrixFile(), mode(md), condition() {
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
	for (size_t i = 0; i < condition.size(); i++) {
		std::cout << i;
		if (i % 3 == 0)
			std::cout << '\n';
	}
}

const std::vector<int>& GameState::get_info() const { return condition; }
const std::vector<std::shared_ptr<Player>> GameState::get_players() const { return players; }
const std::map<std::string, std::string>& GameState::get_rules() const { return rules; }

void GameState::add_players(std::vector<strategies>& strategs) {
	PlayerFabric fabric;
	for (strategies str : strategs) {
		std::shared_ptr<Player> newPlayer = fabric.make_player(str);
		players.push_back(newPlayer);
	}
}

void GameState::start() {
	arbitrator arb(*this);
	for (size_t i = 0; i < nSteps; i++)
		arb.round();
}

GameState::~GameState() {};


