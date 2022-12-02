#pragma once
class sample {
public:
	sample();
	sample(int);
	sample(const sample&);
	
	sample& operator=(const sample&);
	sample& operator+=(const sample&);

	operator int() const;

	~sample();
private:
	int data;
};

sample operator+(const sample&, const sample&);
