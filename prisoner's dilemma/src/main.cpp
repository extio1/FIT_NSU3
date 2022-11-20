#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <list>

#include "gamestate.h"
#include "strenumconv.h"

//виртуальный деструктор!
//перенесены функции-переводчики из string в enum в отдельный hpp
//добавить try-catch к create_players
//добавить try-catch к parser

struct initInfo {
	std::vector<strategies> strats;
	char mode;
	int steps;
	std::string configPath;
	std::string matrixPath;
};

void parse(int argc, char** argv, initInfo& gameinfo) {
	int i = 1;
	for (i; i < argc && argv[i][0] != '-'; i++) //reading only strategies
		gameinfo.strats.push_back(str_to_enum(argv[i]));
	if (i < 3) {
		throw(1);
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
				gameinfo.mode = value[0];
			else if (option == "steps")
				gameinfo.steps = atoi(value.c_str());
			else if (option == "matrix")
				gameinfo.matrixPath = value;
			else if (option == "config")
				gameinfo.configPath = value;
			else {
				throw(2);
			}

		}
	}
}

int main(int argc, char** argv) {
	initInfo gameinfo;

	try {
		parse(argc, argv, gameinfo);
	}
	catch (int parseerrno) {
		switch (parseerrno) {
		case 1:
			std::cerr << "There is not enough participants\n";
			exit(1);
		case 2:
			std::cerr << "Unknown command\n";
			exit(2);
		}
	}

	GameState dilemma(gameinfo.matrixPath, gameinfo.configPath);
	dilemma.start(gameinfo.strats, gameinfo.steps, gameinfo.mode);
}
