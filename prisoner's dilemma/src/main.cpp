#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <list>

#include "strategies.h"
#include "gamestate.h"

std::string to_string(strategies st) {
	switch (st) {
	case(strategies::allcooperate):
		return "allcooperate ";
	case(strategies::alldefect):
		return "alldefect ";
	case(strategies::titfortat):
		return "titfortat ";
	case(strategies::grim):
		return "grim ";
	case(strategies::random):
		return "random ";
	case(strategies::detective):
		return "detective ";
	default:
		return "none ";
	}
}

strategies str_to_enum(char* s) {
	std::string str(s);
	if (str == "alldefect")
		return strategies::alldefect;
	else if (str == "allcooperate")
		return strategies::allcooperate;
	else if (str == "grim")
		return strategies::grim;
	else if (str == "titfortat")
		return strategies::titfortat;
	else if (str == "random")
		return strategies::random;
	else if (str == "detective")
		return strategies::detective;
}

void parse(int argc, char** argv, char* mode, int* steps, std::string* cnfgs, std::string* mtrx, std::vector<strategies>* strats) {
	int i = 1;
	for (i; i < argc && argv[i][0] != '-'; i++) //reading only strategies
		strats->push_back(str_to_enum(argv[i]));
	if (i < 3) {
		std::cout << "There is not enough participants\n";
		exit(1);
	}

	for (i; i < argc; i++) {
		if (argv[i][0] == '-' && argv[i][1] == '-') {
			std::string option;
			std::string value;
			size_t j = 2;
			for (j; argv[i][j] != '='; j++)
				option.push_back(argv[i][j]);
			j++;
			for (j; j < std::string(argv[i]).size(); j++)
				value.push_back(argv[i][j]);

			if (option == "mode")
				*mode = value[0];
			else if (option == "steps")
				*steps = atoi(value.c_str());
			else if (option == "matrix")
				*mtrx = value;
			else if (option == "config")
				*cnfgs = value;
			else {
				std::cout << "Unknown command";
				exit(0);
			}

		}
	}
}

int main(int argc, char** argv) {
	std::vector<strategies> strats; //= { strategies::detective, strategies::allcooperate, strategies::allcooperate };
	strats.reserve(3);
	char mode = 'd';
	int steps = 10;
	std::string configPath;
	std::string matrixPath;
	parse(argc, argv, &mode, &steps, &configPath, &matrixPath, &strats);
	if (strats.size() > 3)
		mode = 't';

	GameState dilemma(matrixPath, configPath);
	dilemma.start(strats, steps, mode);
}
