#pragma once
#include <vector>
#include <string>
#include <memory>

class inaudiofile;
class outaudiofile;
class converter;

class soundproc {
public:
	void use(inaudiofile&, outaudiofile&, std::string&);
private:
	std::vector<converter> conv_list;
};

class converter {
public:
	virtual void launch(inaudiofile&, outaudiofile&) = 0;
	virtual void who_am_i() = 0;
	virtual ~converter();
};

/*
class mute : converter {
public:
	void launch() override;
	void who_am_i() override;
	~mute() override;
};

class mix : converter {
public:
	void launch() override;
	void who_am_i() override;
	~mix() override;
};

class new : converter {
public:
	void launch() override;
	void who_am_i() override;
	~new() override;
};
*/
class copy : public converter {
public:
	void launch(inaudiofile&, outaudiofile&) override;
	void who_am_i() override;
};

class converterfabric {
public:
	std::unique_ptr<converter> make_conv(std::string);
};
