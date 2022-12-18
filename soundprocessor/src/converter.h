#pragma once
#include <vector>
#include <string>
#include <memory>

class inaudiofile;
class outaudiofile;
class converter;
class sample;
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
	~mute();
private:
	void convert(std::vector<unsigned int>&, unsigned int);
	unsigned int start_mute = 0;
	unsigned int end_mute = 0;
	unsigned int time_sec = 0;
	unsigned int tick_counter = 0;
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
private:
	inline void convert(std::vector<sample>&, float);
};

class converterfabric {
public:
	std::unique_ptr<converter> make_conv(const std::string&);
};
