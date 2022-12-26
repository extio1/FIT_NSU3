#pragma once
#include <ios>

class complex {
public:
	complex();
	complex(float, float);

	complex& operator=(const complex&);
	float get_real() const;
	float get_im() const;
	void set_real(float);
	void set_im(float);
private:
	float real;
	float im;
};

template<typename CharT>
auto& operator>>(std::basic_istream<CharT>& os, complex& data) {
	std::string in_str;
	os >> in_str;

	float new_real = 0;
	float new_im = 0;

	std::size_t real_end = in_str.find_first_of('+');
	if (real_end == std::string::npos) {
		new_real = atof(in_str.c_str());
	}
	else {
		new_real = atof(in_str.substr(0, real_end).c_str());
		new_im = atof(in_str.substr(real_end + 1, in_str.size() - real_end).c_str());
	}

	data.set_im(new_im);
	data.set_real(new_real);
	return os;
}

template<typename CharT>
auto& operator<<(std::basic_ostream<CharT>& os, const complex& data) {
	os << data.get_real();
	os << '+';
	os << data.get_im();
	os << 'i';
	return os;
}

