#include "writer.h"
#include "convasciiint.h"

namespace {
	inline void normalize_2_b(int& num) {
		if (num > 32760) {
			(num) = 32760;
		}
		else if (num < -32760) {
			(num) = -32760;
		}
	}
}

writer::writer() : n_bytes_sample(2) { buffer.resize(n_bytes_sample); }
writer::writer(int s) : n_bytes_sample(s) { buffer.resize(n_bytes_sample); }

void writer::write_sample(const int num, std::ofstream& f) {
	int_to_ascii_seq(buffer, num, n_bytes_sample);
	for (int i = 0; i < n_bytes_sample; i++)
		f << buffer[i];
}

void writer::write_num_b(const int num, std::ofstream& f, const int n_bytes) {
	if (buffer.size() < n_bytes)
		buffer.resize(n_bytes);

	int_to_ascii_seq(buffer, num, n_bytes);
	for (int i = 0; i < n_bytes; i++)
		f << buffer[i];
}
