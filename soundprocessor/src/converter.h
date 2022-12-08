#pragma once
#include <vector>
#include <string>
#include <memory>

class inaudiofile;
class outaudiofile;
class converter;
struct command_info;

static std::vector<std::string> list_convert = { "mute", "mix", "amplify", "copy" };

class converter {
public:
	virtual void launch(const command_info& com) = 0;
	virtual void who_am_i() = 0;
	virtual ~converter();
};

class mute : public converter {
public:
	void launch(const command_info& com) override;
	void who_am_i() override;
};

class copy : public converter {
public:
	void launch(const command_info& com) override;
	void who_am_i() override;
};

class mix : public converter {
public:
	void launch(const command_info& com) override;
	void who_am_i() override;
};

class amplify : public converter {
public:
	void launch(const command_info& com) override;
	void who_am_i() override;
};

class converterfabric {
public:
	std::unique_ptr<converter> make_conv(const std::string&);
};
