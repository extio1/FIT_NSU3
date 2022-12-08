#include "writer.h"
#include "convasciiint.h"

WavWriter::WavWriter() : n_bytes_sample(2) { buffer.resize(n_bytes_sample); }
WavWriter::WavWriter(int s) : n_bytes_sample(s) { buffer.resize(n_bytes_sample); }

void WavWriter::write_sample(const int num, std::ofstream& f) {
	int_to_ascii_seq(buffer, num, n_bytes_sample);
	for (int i = 0; i < n_bytes_sample; i++)
		f << buffer[i];
}

void WavWriter::write_num_b(const int num, std::ofstream& f, const int n_bytes) {
	buffer.resize(n_bytes);

	int_to_ascii_seq(buffer, num, n_bytes);
	for (int i = 0; i < n_bytes; i++)
		f << buffer[i];
}
