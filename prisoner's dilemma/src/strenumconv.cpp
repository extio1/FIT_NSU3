#include "strenumconv.h"
#include "excpt.h"

std::string to_string(strategies strat) {
	switch (strat)
	{
	case strategies::alldefect:
		return "alldefect ";
		break;
	case strategies::allcooperate:
		return "allcooperate ";
		break;
	case strategies::titfortat:
		return "titfortat ";
		break;
	case strategies::grim:
		return "grim ";
		break;
	case strategies::detective:
		return "detective ";
		break;
	case strategies::random:
		return "random ";
		break;
	case strategies::notstated:
		return "none ";
		break;
	default:
		break;
	}
}

strategies str_to_enum(std::string strat) {
	if (strat == "alldefect") {
		return strategies::alldefect;
	}
	else if (strat == "allcooperate") {
		return strategies::allcooperate;
	}
	else if (strat == "grim") {
		return strategies::grim;
	}
	else if (strat == "titfortat") {
		return strategies::titfortat;
	}
	else if (strat == "random") {
		return strategies::random;
	}
	else if (strat == "detective") {
		return strategies::detective;
	}
	else {
		throw(invalid_player(strat));
	}
}
