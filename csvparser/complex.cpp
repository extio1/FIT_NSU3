#include "complex.h"

complex::complex(): real(0), im(0) {}
complex::complex(float r, float i): real(r), im(i) {}

complex& complex::operator=(const complex& other) {
	if (this != &other) {
		real = other.real;
		im = other.im;
	}
	return *this;
}

float complex::get_real() const { return real; }
float complex::get_im() const { return im; }
void complex::set_real(float r) { real = r; }
void complex::set_im(float i) { im = i; }
