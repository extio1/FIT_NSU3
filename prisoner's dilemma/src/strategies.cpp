#include <string>
#include <memory>
#include <time.h>
#include <iostream>

#include "strategies.h"

void Player::enter_choice(const std::vector<char>& choice) {
	return;
}
void Player::enter_score(const std::vector<int>& score) {}
void Player::clear() {}

char random::make_step() {
	srand(time(NULL));
	int rnum = rand(); //32768
	char choice = (rnum % 2) ? 'C' : 'D';
	return choice;
}

char alldefect::make_step() {
	return 'D';
}

char allcooperate::make_step() {
	return 'C';
}

char titfortat::make_step() {
	for (char ch : prevGameChoice) {
		if (ch == 'D') {
			srand(time(NULL));
			int rnum = rand(); //32768
			if (rnum < 655)
				return 'C';
			return 'D';
		}
	}
	return 'C';
}
void titfortat::enter_choice(const std::vector<char>& choice) {
	prevGameChoice = choice;
}
void titfortat::clear() {
	for (int i = 0; i < 2; i++)
		prevGameChoice[i] = 0;
}
titfortat::~titfortat(){};

grim::grim() : grimTrigger(false) {}
char grim::make_step() {
	if (grimTrigger) {
		return 'D';
	}
	else {
		for (char ch : prevGameChoice) {
			if (ch == 'D') {
				grimTrigger = true;
				return 'D';
			}
		}
	}
	return 'C';
}
void grim::enter_choice(const std::vector<char>& choice) {
	prevGameChoice = choice;
}
void grim::clear() {
	grimTrigger = false;
	for (int i = 0; i < 2; i++)
		prevGameChoice[i] = 0;
}
grim::~grim(){};

detective::detective() : nstep(1), mode(0) {}
char detective::like_titfortat() {
	for (char ch : choicehistory) {
		if (ch == 'D') {
			srand(time(NULL));
			int rnum = rand(); //32768
			if (rnum < 655)
				return 'C';
			return 'D';
		}
	}
	return 'C';
}
char detective::make_step() {
	if (nstep <= 4) {
		if (nstep % 2 != 0) {
			nstep++;
			return 'C';
		}
		else {
			nstep++;
			return 'D';
		}
	}
	else {
		if (mode != 0) {
			if (mode == 1) {
				return 'D';
			}
			else {
				return like_titfortat();
			}
		}
		else {
			for (char c : choicehistory)
				if (c == 'D') {
					mode = 2;
					return like_titfortat();
				}
			mode = 1;
			return 'D';
		}
	}
}
void detective::enter_choice(const std::vector<char>& choice) {
	if (nstep <= 4) { //в первые ходы накапливает информацию, затем начинает запоминать только предыдущий раунд
		for (char c : choice)
			choicehistory.push_back(c);
	}
	else {
		choicehistory = choice;
	}
}
detective::~detective(){}

std::shared_ptr<Player> PlayerFabric::make_player(strategies strat) {
	if (strat == strategies::alldefect)
		return std::make_shared<alldefect>();
	else if (strat == strategies::allcooperate)
		return std::make_shared<allcooperate>();
	else if (strat == strategies::titfortat)
		return std::make_shared<titfortat>();
	else if (strat == strategies::grim)
		return std::make_shared<grim>();
	else if (strat == strategies::detective)
		return std::make_shared<detective>();
	else if (strat == strategies::random)
		return std::make_shared<random>();
	else
		return nullptr;
}
