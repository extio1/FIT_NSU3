#include "wavinfo.h"
#include <fstream>
#include <iostream>
#include <string>

namespace {
	int little_to_big_endian_byte(int num) {
		int outn;
		for (int i = 0; i < 8; i++) {
			outn = 0;
		}
		return outn;
	}
	int ascii_seq_to_int(const char* ascii, const int size) {
		int num = 0;
		for (int i = size-1; i >= 0; i--) {
			unsigned char piece = (ascii[i] < 0) ? (ascii[i] + 256) : ascii[i];
			num <<= 8;
			num += piece;
		}
		return num;
	}
}

void wavinfo::read_header(std::string path) {
	std::ifstream wavin(path);
	char buffer[5];
	buffer[4] = '\0';
	if (wavin.is_open()) {
		int data;

		wavin.read(buffer, 4);
		std::cout << buffer << '\n'; //RIFF chunkId

		wavin.read(buffer,4);
		std::cout << ascii_seq_to_int(buffer, 4) << '\n'; //chunkSize

		wavin.read(buffer, 4);
		std::cout << buffer << '\n'; //WAVE format

		wavin.read(buffer, 4);
		std::cout << buffer << '\n'; //fmt subchunk1Id

		//все что сверху должно быть всегда, если нет, кинуть исключение

		wavin.read(buffer, 4);
		std::cout << ascii_seq_to_int(buffer, 4) << '\n'; //subchunk1Size 

		wavin.read(buffer, 2);
		std::cout << ascii_seq_to_int(buffer, 2) << '\n'; //audioFormat

		wavin.read(buffer, 2);
		std::cout << ascii_seq_to_int(buffer, 2) << '\n'; //audioFormat

		wavin.read(buffer, 4);
		std::cout << ascii_seq_to_int(buffer, 4) << '\n'; //sampleRate

		wavin.read(buffer, 4);
		std::cout << ascii_seq_to_int(buffer, 4) << '\n'; //byteRate

		wavin.read(buffer, 2);
		std::cout << ascii_seq_to_int(buffer, 2) << '\n'; //blockAlign

		wavin.read(buffer, 2);
		std::cout << ascii_seq_to_int(buffer, 2) << '\n'; //bitsPerSample
		wavin.read(buffer, 4);
		std::cout << buffer << '\n'; //LIST?
		if (!strcmp(buffer,"LIST")) { //если есть какая-то доп.информация. То запишем ее в отдельный txt файл
			std::ofstream extrainfo("extrainformation.txt");
			if (extrainfo.is_open()) {
				wavin.read(buffer, 4);
				int size = ascii_seq_to_int(buffer, 4);
				for (int i = 0; i < size; ++i) {
					extrainfo << wavin.get();
				}
			}
			else {
				std::cerr << "Error while writing extra information about .wav file.";
			}
		}
		else {
			std::cout << "AAAAAAAAAA";
		}

		wavin.read(buffer, 4);
		std::cout << buffer << '\n'; //"data"	

		wavin.read(buffer, 4);
		std::cout << ascii_seq_to_int(buffer, 4) << '\n'; //data size	

	}
	else {
		throw; //кидать ошибку об не открытии файла
	}
}
