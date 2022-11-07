#pragma once
class GameState;

class arbitrator {
private:
	GameState& game;
public:
	arbitrator(GameState&);
	void round();
	~arbitrator();
};
