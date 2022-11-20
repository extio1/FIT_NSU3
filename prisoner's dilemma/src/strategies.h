#pragma once
#include <string>
#include <memory>
#include <vector>

class GameState;
enum class strategies { alldefect, allcooperate, titfortat, grim, detective, random, notstated };

class Player {
public:
	virtual char make_step() = 0;
	virtual void enter_score(const std::vector<int>& score);
	virtual void enter_choice(const std::vector<char>& choice);
	virtual void clear();
	virtual ~Player();
};

class random : public Player { //рандом, что еще сказать
public:
	char make_step();
};

class alldefect : public Player { //всегда кооперироваться
public:
	char make_step();
};

class allcooperate : public Player { //всегда предавать
public:
	char make_step();
};

class titfortat : public Player { // "глаз за глаз", если кто-то предал, то мстит, иначе кооперируется. Первый ход всегда не предаёт
private:						  // кроме того имеет шанс в ~2% скооперироваться, несмотря на то, что кто-то предал
	std::vector<char> prevGameChoice;
public:
	char make_step();
	void enter_choice(const std::vector<char>& choice);
	void clear();
	~titfortat();
};

class grim : public Player { //обидчивая стратегия, если кто-то предал, предаёт до конца игры
private:
	std::vector<char> prevGameChoice;
	bool grimTrigger;
public:
	grim();
	char make_step();
	void enter_choice(const std::vector<char>& choice);
	void clear();
	~grim();
};

class detective : public Player { //первые 4-е хода CDCD, если со строны противника было предательство, будет вести себя как
								  //titfortat. Если не было D, то всегда будет предавать.
private:
	std::vector<char> choicehistory;
	int nstep;
	int mode; //0 - неопределенный, 1 - alldefect, 2 - titfortat
public:
	int show_mode();
	std::vector<char> show_mat();
	detective();
	char like_titfortat();
	char make_step();
	void enter_choice(const std::vector<char>& choice);
	~detective();
};

class PlayerFabric {
public:
	std::shared_ptr<Player> make_player(strategies strat);
};
