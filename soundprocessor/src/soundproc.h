#pragma once

struct command_info;

class soundproc {
public:
	void use(const command_info&) const;
	void help();
};
