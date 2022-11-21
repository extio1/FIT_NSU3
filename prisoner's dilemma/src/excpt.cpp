#include "excpt.h"
#include "strenumconv.h"

const char* invalid_command::what() const noexcept {
	return wrong_command.c_str();
}
invalid_command::invalid_command(std::string ername): wrong_command(ername) {}
invalid_command::invalid_command() : wrong_command("<Unknown command>") {}


const char* invalid_player::what() const noexcept {
	return player_name.c_str();
}
invalid_player::invalid_player(strategies strat) : player_name(to_string(strat)) {}
invalid_player::invalid_player(std::string plname) : player_name(plname) {}
invalid_player::invalid_player() : player_name("<Unknown player>") {}

int not_enough_players::how_many() const noexcept {
	return num_of_plrs;
}
not_enough_players::not_enough_players(int n) : num_of_plrs(n) {}
not_enough_players::not_enough_players() : num_of_plrs(-1) {}
