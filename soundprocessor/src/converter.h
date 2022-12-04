#pragma once
#include <vector>
#include <string>
#include <memory>

class inaudiofile;
class outaudiofile;
class converter;
struct command_info;

class soundproc {
public:
	void use(const command_info&) const;
private:
	std::vector<converter> conv_list;
};

class converter {
public:
	virtual void launch(const command_info& com) = 0;
	virtual void who_am_i() = 0;
	virtual ~converter();
};


class mute : public converter {
public:
	mute();
	//mute(unsigned int, unsigned int);
	void launch(const command_info& com) override;
	void who_am_i() override;
	/*
private:
	unsigned int begin;
	unsigned int end;*/
};

class copy : public converter {
public:
	void launch(const command_info& com) override;
	void who_am_i() override;
};

class converterfabric {
public:
	std::unique_ptr<converter> make_conv(std::string);
};
