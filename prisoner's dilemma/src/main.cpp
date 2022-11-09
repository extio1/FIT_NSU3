#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <list>
//#include <C:\boost_1_80_0\boost\algorithm\>

#include "strategies.h"
#include "gamestate.h"

strategies str_to_enum(char* s) {
	std::string str(s);
	if (str == "alldefect")
		return strategies::alldefect;
	else if (str == "allcooperate")
		return strategies::allcooperate;
}
/*
//парсер недописан
void parse(int argc, char** argv, char* mode, unsigned int* steps, std::string* cnfg, std::string* mtrx, std::vector<strategies> strats) {
	size_t i = 1;
	for (i; i < argc && argv[i][0] != '-'; i++) //reading only strategies
		strats.push_back(str_to_enum(argv[i]));
	if (i < 4) {
		std::cout << "There is not enough participants\n";
		exit(0);
	}

	for (i; i < argc; i++) {
	}
}*/

//mode, скорее всего, не надо хранить в gamestate
int main(int argc, char** argv) {
	
	std::vector<strategies> strats = { strategies::allcooperate, strategies::alldefect, strategies::titfortat, strategies::grim };
	strats.reserve(3);
	char mode = 't';
	unsigned int steps = 6;
	std::string configPath;
	std::string matrixPath;
	/*
	//parse(argc, argv, &mode, &steps, &configPath, &matrixPath, &strats);
	//GameState dilemma(steps, configPath, matrixPath, mode);
	*/
	GameState dilemma(steps, configPath, matrixPath, mode);
	dilemma.start(strats, mode);
}
