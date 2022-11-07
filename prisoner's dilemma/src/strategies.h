#pragma once
#include <string>
#include <memory>

class GameState;

enum class strategies;

class Player {
public:
	virtual char make_step(GameState&) = 0;
	//virtual ~Player() = 0;
};

class alldefect : private Player {
public:
	char make_step(GameState& game);
};

class allcooperate : private Player {
public:
	char make_step(GameState& game);
};

class PlayerFabric {
public:
	std::shared_ptr<Player> make_player(strategies strats);
};
