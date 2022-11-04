#include <iostream>
#include <vector>
#include <string>
//#include "strategies.cpp"

class GameInfo {
private:
	unsigned int nSteps;
	unsigned int nPlayers;
	char mode; // d = detailed, f = fast, t = tournament
	std::string configPath;
	std::string matrixFile;
	std::vector<int> condition; //contains current game-matrix, the score
	std::vector<int> rules; //contains rules of score
public:
	GameInfo() : nSteps(0), nPlayers(0), mode('d'), condition(), rules(),
		configPath(), matrixFile() {};
	GameInfo(unsigned int nstps, unsigned int nplrs, std::string cnfg, std::string mtx, char md = 'd') :
		nSteps(nstps), nPlayers(nplrs), configPath(cnfg), matrixFile(mtx), mode(md), condition() {
		rules.resize(6);
		rules = { 0, 7, 3, 1, 9, 5 }; //    DD   CC   CD  
									  // C  0    7    3
									  // D  1    9    5
	}

	void print_info() const {
		for (int i = 0; i < condition.size(); i++) {
			std::cout << i;
			if (i % 3 == 0)
				std::cout << '\n';
		}
	}
	const std::vector<int>& get_info() const { return condition; }
	const std::vector<int>& get_rules() const { return rules; }

	~GameInfo(){};
};

class Player {
protected:
	const GameInfo& game;
public:
	virtual char make_step() = 0;
	virtual ~Player() {}
};

class arbitrator {
private:
	std::vector<Player*> players;
	GameInfo& game;
public:
	void round() {};
};

int main(){
	return 0;
}
