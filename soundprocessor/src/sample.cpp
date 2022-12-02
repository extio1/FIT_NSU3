#include "sample.h"

sample::sample(): data(0) {}
sample::sample(int d){
	if (d > 32760) {
		d -= 32760;
		d = -d;
	}
	data = d;
}
sample::sample(const sample& other): data(other.data) {}

sample& sample::operator=(const sample& other) {
	if (this != &other) {
		data = other.data;
	}
	return *this;
}

sample& sample::operator+=(const sample& other) {
	int sum = data + other.data;
	if (sum < -32760) {
		sum = -32760;
	}
	else if (sum > 32760) {
		sum = 32760;
	}

	data = sum;
	return *this;
}


sample operator+(const sample& op1, const sample& op2) {
	sample temp = op1;
	temp += op2;
	return temp;
}

sample::operator int() const {
	int sampleint = data;
	if (sampleint < 0) {
		sampleint = -data + 32760;
	}
	return sampleint;
}

sample::~sample() {}
