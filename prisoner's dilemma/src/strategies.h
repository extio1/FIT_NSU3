#pragma once
#include <string>
#include <memory>
#include <vector>

class GameState;
enum class strategies { alldefect, allcooperate, titfortat, grim };

class Player {
public:
	virtual char make_step() = 0;
	virtual void enter_score(const std::vector<int>& score);
	virtual void enter_choice(const std::vector<char>& choice);
	//virtual ~Player() = 0;
};

class alldefect : public Player {
public:
	char make_step();
};

class allcooperate : public Player {
public:
	char make_step();
};

class titfortat : public Player {
public:
	char make_step();
};

class grim : public Player {
private:
	std::vector<char> prevGameChoice;
	bool grimTrigger;
public:
	grim(): grimTrigger(false){}
	char make_step();
	void enter_choice(const std::vector<char>& choice);
};

class PlayerFabric {
public:
	std::shared_ptr<Player> make_player(strategies strat);
};
