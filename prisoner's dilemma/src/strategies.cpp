
#include <string>
#include <memory>

#include "strategies.h"

void Player::enter_choice(const std::vector<char>& choice) {
	return;
}
void Player::enter_score(const std::vector<int>& score) {
	return;
}

char alldefect::make_step() {
	return 'D';
}

char allcooperate::make_step() {
	return 'C';
}

char titfortat::make_step() {
	return 'C';
}

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


std::shared_ptr<Player> PlayerFabric::make_player(strategies strat) {
	if (strat == strategies::alldefect)
		return std::make_shared<alldefect>();
	else if (strat == strategies::allcooperate)
		return std::make_shared<allcooperate>();
	else if (strat == strategies::titfortat)
		return std::make_shared<titfortat>();
	else if (strat == strategies::grim)
		return std::make_shared<grim>();
	else
		return nullptr;
}
