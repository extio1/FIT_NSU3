#include "sample.h"
#include <climits>

sample::sample(): data(0) {}
sample::sample(unsigned int d){
	if(d == 0)
		data = 0;
	if (d > SHRT_MAX) {
		data = d - USHRT_MAX;
	}
	else {
		data = d;
	}
	
}
sample::sample(const sample& other): data(other.data) {}

void sample::normalize() {
	if (data < SHRT_MIN) {
		data = SHRT_MIN;
	}
	else if (data > SHRT_MAX) {
		data = SHRT_MAX;
	}
}
void sample::normalize(int& d) {
	if (d < SHRT_MIN) {
		d = SHRT_MIN;
	}
	else if (data > SHRT_MAX) {
		d = SHRT_MAX;
	}
}

sample& sample::operator=(const sample& other) {
	if (this != &other) {
		data = other.data;
	}
	return *this;
}

sample& sample::operator+=(const sample& other) {
	int sum = data + other.data;
	normalize(sum);
	data = sum;

	return *this;
}

sample& sample::operator/=(const sample& other) {
	data /= other.data;
	return *this;
}

sample& sample::operator*=(int p) {
	data *= p;
	normalize();
	return *this;
}

sample& sample::operator*=(float p) {
	data *= p;
	normalize();
	return *this;
}

sample operator/(const sample& op1, const sample& op2) {
	sample temp = op1;
	temp /= op2;
	return temp;
}

sample operator+(const sample& op1, const sample& op2) {
	sample temp = op1;
	temp += op2;
	return temp;
}

sample operator*(const sample& op1, int op2) {
	sample temp = op1;
	temp *= op2;
	return temp;
}

sample operator*(const sample& op1, float op2) {
	sample temp = op1;
	temp *= op2;
	return temp;
}

sample::operator unsigned int() const {
	if (data < 0) {
		return data + USHRT_MAX;
	}
	else {
		return data;
	}
	
}

sample::~sample() {}
