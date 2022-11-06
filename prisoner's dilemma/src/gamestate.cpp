#include <vector>
#include <string>
#include <map>
#include <iostream>

extern class Player;
extern enum class strategies;

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
	GameState() : nSteps(0), mode('d'), condition(), rules(),
		configPath(), matrixFile() {};

	GameState(unsigned int nstps, char md = 'd') :
		nSteps(nstps), mode(md), condition() {}

	GameState(unsigned int nstps, std::string cnfg, std::string mtx, char md = 'd') :
		nSteps(nstps), configPath(), matrixFile(), mode(md), condition() {
		if (!cnfg.empty()) {
			//do something
		}
		if (!mtx.empty()) {
			//make other rules
		}
		else {
			rules = { {"CCC", "777"}, {"CCD", "339"}, {"CDC", "393"}, {"DCC", "933"},
					  {"CDD", "055"}, {"DCD", "505"}, {"DDC", "550"}, {"DDD", "111"} };
		}
	}

	void print_info() const {
		for (int i = 0; i < condition.size(); i++) {
			std::cout << i;
			if (i % 3 == 0)
				std::cout << '\n';
		}
	}

	const std::vector<int>& get_info() const { return condition; }
	const std::map<std::string, std::string>& get_rules() const { return rules; }

	~GameState() {};
};
