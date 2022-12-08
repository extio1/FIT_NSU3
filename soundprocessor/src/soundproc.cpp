#include "soundproc.h"
#include "converter.h"
#include "configfileparser.h"
#include "excpts.h"
#include <iostream>

void soundproc::use(const command_info& com) const {
	converterfabric fabric;
	try {
		auto conv = fabric.make_conv(com.name);
		conv->launch(com);
	}
	catch (conv_wrong_name cwn) {
		std::cerr << "Converter <" << cwn.what_name() << "> does not exist. Use -h to see the list of supported convertors.\n";
	}
	catch (conv_not_enought_args cnea) {
		std::cerr << "There is not enough arguments for " << cnea.what_name() << ". Use -h to see the list of supported convertors.\n";
	}
}


void soundproc::help() {
	converterfabric fabric;
	for (std::string name : list_convert) {
		auto conv = fabric.make_conv(name);
		conv->who_am_i();
	}
}
