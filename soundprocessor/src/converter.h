#pragma once
#include <vector>

class audiofile;
class inaudiofile;
class outaudiofile;
class converter;

class soundproc {
public:
	void use(inaudiofile&, outaudiofile&);
private:
	std::vector<converter> conv_list;
};

class converter {
public:
	virtual void launch(audiofile&, audiofile&) = 0;
	virtual void who_am_i() = 0;
	virtual ~converter() {};
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
class nothing : public converter {
public:
	//void launch(audiofile& f1, audiofile& f2) override;
	~nothing();
};
