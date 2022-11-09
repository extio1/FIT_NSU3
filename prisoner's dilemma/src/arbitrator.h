
#pragma once
#include <vector>
#include <memory>
#include <string>

class GameState;
class Player;
enum class strategies;

class arbitrator {
private:
	GameState& game;
	std::vector<std::shared_ptr<Player>> players;
public:
	arbitrator(GameState&);
	void create_players(const std::vector<strategies>&);
	std::vector<int> round(std::string* = nullptr);
	~arbitrator();
};
