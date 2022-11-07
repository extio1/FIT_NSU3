#pragma once
#include <vector>
#include <string>
#include <map>
#include <memory>

class Player;
enum class strategies;

class GameState {
private:
	unsigned int nSteps;
	char mode; // d = detailed, f = fast, t = tournament
	std::string configPath;
	std::string matrixFile;
	std::vector<int> condition; //contains current game-matrix, the score
	std::map<std::string, std::string> rules; //contains rules of score
	std::vector<std::shared_ptr<Player>> players; //the vector of strategies
public:
	GameState();
	GameState(unsigned int, char = 'd');
	GameState(unsigned int, std::string, std::string, char md = 'd');
	void print_info() const;
	const std::vector<int>& get_info() const;
	const std::vector<std::shared_ptr<Player>> get_players() const;
	const std::map<std::string, std::string>& get_rules() const;
	void add_players(std::vector<strategies>&);
	void start();
	~GameState();
};
