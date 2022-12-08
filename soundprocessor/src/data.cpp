#include "audiofile.h"
#include "convasciiint.h"
#include "writer.h"
#include "excpts.h"

#include <fstream>
#include <vector>
#include <memory>

wavdata::wavdata(): writer(std::make_unique<WavWriter>()), size_data_chunk(512), bytes_per_sample(2), cur_pos(0), data_pos_begin(0), data_size(0) {}

void wavdata::skip(int size) {
	cur_pos += size * bytes_per_sample;
}

void wavdata::find_begin(std::ifstream& in, const char* name) {
	int saved_position = in.tellg();
	in.seekg(0);

	char ch = 0;
	int not_found_begin_counter = 0;
	while (not_found_begin_counter < 4 && !in.eof()) {
		in >> ch;
		if (ch == 'd' && not_found_begin_counter == 0)
			not_found_begin_counter++;
		else if (ch == 'a' && not_found_begin_counter == 1)
			not_found_begin_counter++;
		else if (ch == 't' && not_found_begin_counter == 2)
			not_found_begin_counter++;
		else if (ch == 'a' && not_found_begin_counter == 3) {
			not_found_begin_counter++;
			break;
		}
		else
			not_found_begin_counter = 0;
	}

	bool data_was_found = (not_found_begin_counter == 4);
	if (!data_was_found)
		throw wrong_header(name, "data");

	char buffer[4];
	in.read(buffer, 4);
	data_size = ascii_seq_to_int_le(buffer, 4);

	data_pos_begin = in.tellg();
	cur_pos = data_pos_begin;

	in.seekg(saved_position);
}

void wavdata::read(std::vector<unsigned int>& outarr, std::ifstream& f) {
	char buffer[4];
	
	if(outarr.size() != size_data_chunk)
		outarr.resize(size_data_chunk);
	if (f.tellg() != cur_pos)
		f.seekg(cur_pos);

	int new_pos = 0;
	for (int i = 0; i < size_data_chunk; i++) {
		if (!f.eof()) {
			f.read(buffer, bytes_per_sample);
			outarr[new_pos++] = ascii_seq_to_int_le(buffer, bytes_per_sample);
		}
		else {
			outarr.resize(i);
			break;
		}
	}

	cur_pos += new_pos * bytes_per_sample;
}


void wavdata::write(std::vector<unsigned int>& arr, std::ofstream& f) {
	for (unsigned int i : arr)
		writer->write_sample(i, f);
}

wavdata::~wavdata() {}
