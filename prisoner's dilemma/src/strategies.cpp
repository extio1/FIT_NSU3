
#include <string>
#include <memory>

extern class GameState;
enum class strategies { alldefect, allcooperate };

class Player {
public:
	virtual char make_step(GameState&) = 0;
	//virtual ~Player() = 0;
};

class alldefect : private Player {
public:
	char make_step(GameState& game) {
		return 'D';
	}
};

class allcooperate : private Player {
public:
	char make_step(GameState& game) {
		return 'C';
	}
};

class PlayerFabric {
public:
	std::shared_ptr<Player> make_player(strategies strats) {
		if (strats == strategies::alldefect)
			std::shared_ptr<alldefect> obj = std::make_shared<alldefect>();
		else if(strats == strategies::allcooperate)
			std::shared_ptr<allcooperate> obj = std::make_shared<allcooperate>();
	}
};
