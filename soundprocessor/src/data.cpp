#include "audiofile.h"
#include "convasciiint.h"
#include "writer.h"

#include <fstream>
#include <vector>

wavdata::wavdata(): size_data_chunk(512), eof(false), cur_pos(0), data_pos_begin(0), data_size(0) {}

void wavdata::test() {
	std::cout << data_pos_begin << ' ' << cur_pos << '\n';
}

void wavdata::find_begin(std::ifstream& in) {
	int saved_position = in.tellg();
	in.seekg(0);

	char ch = 0;
	int not_found_begin_counter = 0;
	while (not_found_begin_counter < 4) {
		in >> ch;
		if (ch == 'd' && not_found_begin_counter == 0)
			not_found_begin_counter++;
		else if (ch == 'a' && not_found_begin_counter == 1)
			not_found_begin_counter++;
		else if (ch == 't' && not_found_begin_counter == 2)
			not_found_begin_counter++;
		else if (ch == 'a' && not_found_begin_counter == 3)
			not_found_begin_counter++;
		else
			not_found_begin_counter = 0;
	}

	char buffer[4];
	in.read(buffer, 4);
	data_size = ascii_seq_to_int_le(buffer, 4);

	data_pos_begin = in.tellg();
	cur_pos = data_pos_begin;

	in.seekg(saved_position);
}

void wavdata::read(std::vector<int>& outarr, std::ifstream& f) {
	char buffer[4];

	if(outarr.size() != size_data_chunk)
		outarr.resize(size_data_chunk);

	if (f.tellg() != cur_pos)
		f.seekg(cur_pos);

	int new_pos = 0;
	for (int i = 0; i < size_data_chunk; i++) {
		if (cur_pos + new_pos <= data_size) {
			for (int j = 0; j < 2; j++) {
				f.get(buffer[j]);
			}
			outarr[new_pos++] = ascii_seq_to_int_le(buffer, 2);
		}
		else {
			eof = true;
			break;
		}
	}


	if (cur_pos + (new_pos + 1) * 2 < data_size) {
		cur_pos += new_pos * 2;
	}
	else {
		cur_pos = data_pos_begin;
		eof = true;
	}
}


void wavdata::set_begin(unsigned int begin_pos) {
	data_pos_begin = begin_pos;
	cur_pos = begin_pos;
}

void wavdata::write(std::vector<int>& arr, std::ofstream& f) {
	writer writer;
	for (int i = 0; i < arr.size() && arr[i] != -1; i++)
		writer.write_sample(arr[i], f);
}

bool wavdata::endof() {
	return eof;
}

wavdata::~wavdata() {}
