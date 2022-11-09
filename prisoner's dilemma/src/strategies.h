#pragma once
#include <string>
#include <memory>

class GameState;
enum class strategies { alldefect, allcooperate, titfortat };

class Player {
public:
	virtual char make_step() = 0;
	//virtual ~Player() = 0;
};

class alldefect : public Player {
public:
	char make_step();
	~alldefect();
};

class allcooperate : public Player {
public:
	char make_step();
	~allcooperate();
};

class titfortat : public Player {
public:
	char make_step();
	~titfortat();
};

class PlayerFabric {
public:
	std::shared_ptr<Player> make_player(strategies strat);
};
