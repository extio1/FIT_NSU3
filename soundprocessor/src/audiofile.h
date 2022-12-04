#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <iostream>

class wavheader{
public:

	wavheader();
	void read_header(std::ifstream&);
	void write_header(std::ofstream&);
	void genarate_header(std::ofstream&);
	unsigned int get_sample_rate() const;
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
	//wavdata(std::fstream&); 

	void find_begin(std::ifstream&); //должен кидать о неправильном хедере (не нашел сегмент данных)
	void read(std::vector<int>&, std::ifstream&);
	void write(std::vector<int>&, std::ofstream&);
	void set_begin(unsigned int);
	bool endof();

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
	//audiofile(std::fstream);

	void read_header(std::string&);
	void create_audiofile(const char*);
	bool eof();

	~audiofile();

	std::unique_ptr<wavheader> wheader;

protected:
	std::unique_ptr<wavdata> wdata;
};


class inaudiofile : public audiofile {
public:
	inaudiofile();
	inaudiofile(const char*);
	inaudiofile(const std::string&);

	inaudiofile& operator>>(std::vector<int>&); //читает wav файл (data) и отдает вектор по 512 unsigned int

	~inaudiofile();
private:
	std::ifstream audiostr;
};

class outaudiofile : public audiofile {
public:
	outaudiofile();
	outaudiofile(const std::string&);
	outaudiofile(const char*);

	outaudiofile& operator<<(std::vector<int>&);//пишет в wav файл (data) по 512 unsigned int

	~outaudiofile();
private:
	std::ofstream audiostr;
};
