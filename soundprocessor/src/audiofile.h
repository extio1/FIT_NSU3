#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <iostream>

#include "header.h"
#include "data.h"

class wavheader{
public:

	wavheader();
	wavheader(std::fstream&);
	void read_header(std::fstream&);
	void write_header(std::fstream&);
	void genarate_header(std::ofstream&);
	~wavheader();

private:

	unsigned int RIFF_chunk_size; //размер секции RIFF, размер файла минус 8 байт.

	unsigned short comp_code; //код типа сжатия (для wav 1)
	unsigned short n_of_channels; //число каналов аудито (для wav 1)
	unsigned int sample_rate;  //Число выборок аудиосигнала, приходящихся на секунду.
	unsigned int average_bytes_per_sec; //Величина, показывающая, сколько байт за секунду данных должно
										 //быть пропущено через цифроаналоговый преобразователь (D/A converter, DAC)
	unsigned short block_align; //Количество байт на одну выборку.
	unsigned short sign_bits_per_sample; //Величина указывает количество бит, формирующих каждую выборку сигнала. 
									     //Обычно эта величина 8, 16, 24 или 32.

	std::string extra_info_path; //путь до файла с доп информацией (секция LIST)
};

class wavdata {
public:

	wavdata();
	wavdata(std::fstream&); //должен кидать о неправильном хедере (не нашел сегмент данных)
	void read(std::vector<int>&, std::fstream&);
	~wavdata();
	void test();

private:

	bool eof;
	unsigned int cur_pos;
	unsigned int data_size;
	unsigned int data_pos_begin; //сдвиг до начала секции данных (тут щас возможно надо будет сдвинуться на 1 символ вперед)
	const int size_data_chunk; //размер читаемых данных за 1 шаг

};

class audiofile {
public:

	audiofile();
	audiofile(const char*);

	audiofile& operator>>(std::vector<int>&);//читает wav файл и отдает вектор по 512 unsigned int
	void read_header(std::string&);
	void create_audiofile(const char*);

	~audiofile();

private:
	std::unique_ptr<wavheader> wheader;
	std::unique_ptr<wavdata> wdata;
	std::fstream audiostr;
};
