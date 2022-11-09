
#include <string>
#include <memory>

#include "strategies.h"

char alldefect::make_step() {
	return 'D';
}
alldefect::~alldefect(){}

char allcooperate::make_step() {
	return 'C';
}
allcooperate::~allcooperate() {}

char titfortat::make_step() {
	return 'C';
}
titfortat::~titfortat() {}

std::shared_ptr<Player> PlayerFabric::make_player(strategies strat) {
	if (strat == strategies::alldefect)
		return std::make_shared<alldefect>();
	else if (strat == strategies::allcooperate)
		return std::make_shared<allcooperate>();
	else if (strat == strategies::titfortat)
		return std::make_shared<titfortat>();
	else
		return nullptr;
}
