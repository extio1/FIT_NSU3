#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <list>

#include "gamestate.h"
#include "strenumconv.h"
#include "excpt.h"

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
	if (i < 4) {
		throw(not_enough_players(i-1));
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
				throw(invalid_command(option));
			}
		}
	}
}

int main(int argc, char** argv) { //добавить, чтобы узнать, что за неизвестная команда
	initInfo gameinfo;
	
	try {
		parse(argc, argv, gameinfo);
	}
	catch (not_enough_players nep) {
		std::cerr << "There is " << nep.how_many() << " of 3 players\n";
		return 1;
	}
	catch(invalid_command ic){
		std::cerr << "Unknown command: " << ic.what();
		return 1;
	}
	catch (invalid_player ip) {
		std::cout << "Error while creating player " << ip.what() << '\n';
	}

	GameState dilemma(gameinfo.matrixPath, gameinfo.configPath);
}
