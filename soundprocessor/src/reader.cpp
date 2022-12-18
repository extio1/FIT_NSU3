#include "reader.h"
#include "convasciiint.h"

int WavReader::read_int_b(std::ifstream& stream, int length_b) {
	buffer.resize(length_b);
	for (int i = 0; i < length_b; i++) {
		buffer[i] = stream.get();
	}
	return ascii_seq_to_int(buffer, length_b);
}
