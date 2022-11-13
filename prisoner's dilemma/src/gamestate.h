#pragma once
#include <vector>
#include <string>
#include <map>
#include <memory>

class Player;
enum class strategies;

class GameState {
public:
	GameState();
	GameState(std::string, std::string = "");
	friend void assign_matrix(std::string, GameState&);

	const std::map<std::string, std::string>& get_rules() const;
	void start(const std::vector<strategies>&, const int nsteps, const char mode = 'd');

	~GameState();
private:

	std::string configPath;
	std::map<std::string, std::string> rules; //contains rules of score
};
