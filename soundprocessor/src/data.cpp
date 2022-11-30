#include "audiofile.h"
#include "convasciiint.h"
#include <fstream>
#include <vector>

wavdata::wavdata(): size_data_chunk(512), eof(false), cur_pos(0), data_pos_begin(0), data_size(0) {}

void wavdata::test() {
	std::cout << data_pos_begin << ' ' << cur_pos << '\n';
}

wavdata::wavdata(std::fstream& in): size_data_chunk(512), eof(false) {
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

void wavdata::read(std::vector<int>& outarr, std::fstream& f) {
	char buffer[4];

	int new_pos = 0;
	for (int i = 0; i < size_data_chunk; i++) {
		if (cur_pos + new_pos + 1 <= data_size) {
			f.read(buffer, 4);
			outarr[new_pos++] = ascii_seq_to_int_le(buffer, 4);
		}
		else {
			eof = true;
			break;
		}
	}
	if (cur_pos + new_pos + 1 < data_size) {
		cur_pos += new_pos + 1;
	}
	else {
		cur_pos = data_pos_begin;
	}
}


wavdata::~wavdata() {}
