#include "converter.h"
#include "audiofile.h"
#include "sample.h"
#include "excpts.h"
#include "configfileparser.h"
#include <vector>
#include <string>
#include <string>

converter::~converter(){}

std::unique_ptr<converter> converterfabric::make_conv(const std::string& name) {
	if (name == "copy") {
		return std::make_unique<copy>();
	}
	else if (name == "mute") {
		return std::make_unique<mute>();
	}
	else if (name == "mix"){
		return std::make_unique<mix>();
	}
	else if (name == "amplify") {
		return std::make_unique<amplify>();
	}
	else {
		throw conv_wrong_name(name.c_str());
	}
}
