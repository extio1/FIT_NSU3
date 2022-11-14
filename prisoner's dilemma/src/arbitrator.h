#pragma once
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
	std::vector<int> scoregame;
	std::vector<int> scoreround;
	std::vector<char> choice;
public:
	arbitrator(GameState&);
	void show_score_game() const;
	void show_score_round() const;
	void show_choice() const;
	size_t who_winner() const;

	void create_players(const std::vector<strategies>&);

	void match();
	void match(const size_t, const size_t, const size_t, const int);
	void tournament(const int);

	~arbitrator();
};
