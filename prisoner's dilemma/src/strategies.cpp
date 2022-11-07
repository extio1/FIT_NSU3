#include <string>
#include <memory>
#include "gamestate.h"
#include "strategies.h"
enum class strategies { alldefect, allcooperate };

char alldefect::make_step(GameState& game) {
	return 'D';
}

char allcooperate::make_step(GameState& game) {
	return 'C';
}

std::shared_ptr<Player> PlayerFabric::make_player(strategies strats) {
	std::shared_ptr<Player> obj;
	if (strats == strategies::alldefect)
		std::shared_ptr<alldefect> obj = std::make_shared<alldefect>();
	else if (strats == strategies::allcooperate)
		std::shared_ptr<allcooperate> obj = std::make_shared<allcooperate>();

	return obj;
}
