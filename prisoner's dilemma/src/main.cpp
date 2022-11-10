#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <list>
//#include <boost\program_options.hpp>

#include "strategies.h"
#include "gamestate.h"



//парсер недописан


//mode, скорее всего, не надо хранить в gamestate
int main(int argc, char** argv) {
	//boost::program_options::options_description desc("General options");

	std::vector<strategies> strats = { strategies::titfortat, strategies::grim, strategies::allcooperate };
	strats.reserve(3);
	char mode = 'f';
	int steps = 10;
	std::string configPath;
	std::string matrixPath = "matrix1.csv";

	//GameState dilemma(argc, argv);
	GameState dilemma(steps, configPath, matrixPath, mode);
	dilemma.start(strats, mode);
}
