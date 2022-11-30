
#include "audiofile.h"
#include <iostream>
#include <fstream>
#include "convasciiint.h"

wavheader::wavheader() : average_bytes_per_sec(0), block_align(0),
						 comp_code(0), n_of_channels(0), sample_rate(0), 
						 sign_bits_per_sample(0), RIFF_chunk_size(0) {}

wavheader::wavheader(std::fstream& in): wavheader() {
	read_header(in);
}

void wavheader::read_header(std::fstream& wavin) {
	char buffer[5];
	buffer[4] = '\0';

	if (wavin.is_open()) {
		wavin.read(buffer, 4);
		//std::cout << buffer << '\n'; //RIFF chunkId

		wavin.read(buffer, 4);
		//std::cout << ascii_seq_to_int_le(buffer, 4) << '\n'; //chunkSize

		RIFF_chunk_size = ascii_seq_to_int_le(buffer, 4);

		wavin.read(buffer, 4);
		//std::cout << buffer << '\n'; //WAVE format

		wavin.read(buffer, 4);
		//std::cout << buffer << '\n'; //fmt subchunk1Id

		//все что сверху должно быть всегда, если нет, кинуть исключение

		wavin.read(buffer, 4);
		//std::cout << ascii_seq_to_int_le(buffer, 4) << '\n'; //размер чанка fmt, должен быть равен 16

		wavin.read(buffer, 2);
		//std::cout << ascii_seq_to_int_le(buffer, 2) << '\n';
		comp_code = ascii_seq_to_int_le(buffer, 2);

		wavin.read(buffer, 2);
		//std::cout << ascii_seq_to_int_le(buffer, 2) << '\n';
		n_of_channels = ascii_seq_to_int_le(buffer, 2);

		wavin.read(buffer, 4);

		sample_rate = ascii_seq_to_int_le(buffer, 4);

		wavin.read(buffer, 4);
		//std::cout << ascii_seq_to_int_le(buffer, 4) << '\n';
		average_bytes_per_sec = ascii_seq_to_int_le(buffer, 4);

		wavin.read(buffer, 2);
		//std::cout << ascii_seq_to_int_le(buffer, 2) << '\n';
		block_align = ascii_seq_to_int_le(buffer, 2);

		wavin.read(buffer, 2);
		//std::cout << ascii_seq_to_int_le(buffer, 2) << '\n';
		sign_bits_per_sample = ascii_seq_to_int_le(buffer, 2);

		wavin.read(buffer, 4);
		//std::cout << buffer << '\n'; //LIST?

		if (!strcmp(buffer, "LIST")) { //если есть какая-то доп.информация. То запишем ее в отдельный txt файл
			std::ofstream extrainfo("extrainformation.txt");
			if (extrainfo.is_open()) {
				wavin.read(buffer, 4);
				int size = ascii_seq_to_int_le(buffer, 4);
				for (int i = 0; i < size; ++i) {
					extrainfo << wavin.get();
				}
			}
			else {
				std::cerr << "Error while writing extra information about .wav file.";
			}
		}
		/*
		wavin.read(buffer, 4);
		//std::cout << buffer << '\n'; //"data"	

		wavin.read(buffer, 4);
		//std::cout << ascii_seq_to_int_le(buffer, 4) << '\n'; //data size	
		data_size = ascii_seq_to_int_le(buffer, 4);*/
	}
	else {
		throw; //кидать ошибку об не открытии файла
	}
}

void wavheader::write_header(std::fstream& wavout) {}
	/*
	if (wavout.is_open()) {
		wavout << 'R' << 'I' << 'F' << 'F';
		//std::cout << buffer << '\n'; //RIFF chunkId

		wavout.read(buffer, 4);
		//std::cout << ascii_seq_to_int_le(buffer, 4) << '\n'; //chunkSize

		wavout.read(buffer, 4);
		//std::cout << buffer << '\n'; //WAVE format

		wavout.read(buffer, 4);
		//std::cout << buffer << '\n'; //fmt subchunk1Id

		//все что сверху должно быть всегда, если нет, кинуть исключение

		wavout.read(buffer, 4);
		//std::cout << ascii_seq_to_int_le(buffer, 4) << '\n'; //размер чанка fmt, должен быть равен 16

		wavout.read(buffer, 2);
		//std::cout << ascii_seq_to_int_le(buffer, 2) << '\n';
		comp_code = ascii_seq_to_int_le(buffer, 2);

		wavout.read(buffer, 2);
		//std::cout << ascii_seq_to_int_le(buffer, 2) << '\n';
		n_of_channels = ascii_seq_to_int_le(buffer, 2);

		wavout.read(buffer, 4);
		//std::cout << ascii_seq_to_int_le(buffer, 4) << '\n';
		sample_rate = ascii_seq_to_int_le(buffer, 4);

		wavout.read(buffer, 4);
		//std::cout << ascii_seq_to_int_le(buffer, 4) << '\n';
		average_bytes_per_sec = ascii_seq_to_int_le(buffer, 4);

		wavout.read(buffer, 2);
		//std::cout << ascii_seq_to_int_le(buffer, 2) << '\n';
		block_align = ascii_seq_to_int_le(buffer, 2);

		wavout.read(buffer, 2);
		//std::cout << ascii_seq_to_int_le(buffer, 2) << '\n';
		sign_bits_per_sample = ascii_seq_to_int_le(buffer, 2);

		wavout.read(buffer, 4);
		//std::cout << buffer << '\n'; //LIST?

		if (!strcmp(buffer, "LIST")) { //если есть какая-то доп.информация. То запишем ее в отдельный txt файл
			std::ofstream extrainfo("extrainformation.txt");
			if (extrainfo.is_open()) {
				wavout.read(buffer, 4);
				int size = ascii_seq_to_int_le(buffer, 4);
				for (int i = 0; i < size; ++i) {
					extrainfo << wavout.get();
				}
			}
			else {
				std::cerr << "Error while writing extra information about .wav file.";
			}
		}

		wavout.read(buffer, 4);
		//std::cout << buffer << '\n'; //"data"	

		wavout.read(buffer, 4);
		//std::cout << ascii_seq_to_int_le(buffer, 4) << '\n'; //data size	
		data_size = ascii_seq_to_int_le(buffer, 4);
	}
	else {
		throw; //кидать ошибку об не открытии файла
	}
}
*/

void wavheader::genarate_header(std::ofstream& f) {
	char buffer[4];

	f.write("RIFF", 4);
	int_to_ascii_seq_le(buffer, 0, 4);
	f.write(buffer, 4);
	f.write("WAVE", 4);
	f.write("fmt ", 4);

	int_to_ascii_seq_le(buffer, 16, 4);
	f.write(buffer, 4);
	int_to_ascii_seq_le(buffer, 1, 2);
	f.write(buffer, 2);
	int_to_ascii_seq_le(buffer, 1, 2);
	f.write(buffer, 2);
	int_to_ascii_seq_le(buffer, 44100, 4);
	f.write(buffer, 4);
	int_to_ascii_seq_le(buffer, 0, 4);
	f.write(buffer, 4);
	int_to_ascii_seq_le(buffer, 0, 2);
	f.write(buffer, 2);
	int_to_ascii_seq_le(buffer, 8, 2);
	f.write(buffer, 2);

	f.write("data", 4);
	int_to_ascii_seq_le(buffer, 0, 4);
	f.write(buffer, 4);

}

wavheader::~wavheader(){}