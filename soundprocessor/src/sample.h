#pragma once
class sample {
public:
	sample();
	sample(unsigned int);
	sample(const sample&);
	
	sample& operator=(const sample&);
	sample& operator+=(const sample&);
	sample& operator/=(const sample&);
	sample& operator*=(int);
	sample& operator*=(float);

	operator unsigned int() const;

	~sample();
private:
	void normalize();
	void normalize(int&);
	int data;
};

sample operator+(const sample&, const sample&);
sample operator/(const sample&, const sample&);
sample operator*(const sample&, int);
sample operator*(const sample&, float);
