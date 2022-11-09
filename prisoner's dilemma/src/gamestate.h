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
	GameState(unsigned int, char = 'd');
	GameState(unsigned int, std::string, std::string, char md = 'd');

	void print_info() const;
	const std::vector<int>& get_info() const;
	const std::map<std::string, std::string>& get_rules() const;

	void start(const std::vector<strategies>&, const char mode = 'd');
	void renew_score(const std::vector<int>&);

	~GameState();

private:

	unsigned int nSteps;
	char mode; // d = detailed, f = fast, t = tournament
	std::string configPath;
	std::string matrixFile;
	std::vector<int> score; //contains the current score
	std::map<std::string, std::string> rules; //contains rules of score

};
