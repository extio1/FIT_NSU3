#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <iostream>

class WavWriter;
class WavReader;
class sample;

class wavheader{
public:

	wavheader();
	void read_header(std::ifstream&, const char* = 0);
	void genarate_header(std::ofstream&);
	unsigned int get_sample_rate() const;
	~wavheader();

private:

	std::string filename;

	unsigned int RIFF_chunk_size; //размер секции RIFF, размер файла минус 8 байт.

	unsigned short comp_code; //код типа сжатия (для wav 1)
	unsigned short n_of_channels; //число каналов аудито (для wav 1)
	unsigned int sample_rate;  //Число выборок аудиосигнала, приходящихся на секунду.
	unsigned int average_bytes_per_sec; //Величина, показывающая, сколько байт за секунду данных должно
										 //быть пропущено через цифроаналоговый преобразователь (D/A converter, DAC)
	unsigned short block_align; //Количество байт на одну выборку.
	unsigned short sign_bits_per_sample; //Величина указывает количество бит, формирующих каждую выборку сигнала. 
									     //Обычно эта величина 8, 16, 24 или 32.
};


class wavdata {
public:

	wavdata();
	void find_begin(std::ifstream&, const char*);
	void read(std::vector<unsigned int>&, std::ifstream&);
	void write(std::vector<unsigned int>&, std::ofstream&);
	void skip(int);
	~wavdata();

private:
	
	std::unique_ptr<WavWriter> writer;
	std::unique_ptr<WavReader> reader;

	unsigned int cur_pos;
	unsigned int data_size;
	unsigned int data_pos_begin;

	const int size_data_chunk;
	const int bytes_per_sample;

};


class audiofile {
public:

	audiofile();
	void read_header(std::string&);
	void create_audiofile(const char*);
	~audiofile();
	
protected:

	std::unique_ptr<wavheader> wheader;
	std::unique_ptr<wavdata> wdata;

};


class inaudiofile : public audiofile {
public:

	inaudiofile();
	inaudiofile(const char*);
	inaudiofile(const std::string&);

	unsigned int get_sample_rate() const;
	bool eof();
	void skip(int);
	inaudiofile& operator>>(std::vector<unsigned int>&); //читает wav файл (data) и отдает вектор по 512 unsigned int
	inaudiofile& operator>>(std::vector<sample>&);

	~inaudiofile();

private:

	std::ifstream audiostr;

};


class outaudiofile : public audiofile {
public:

	outaudiofile();
	outaudiofile(const std::string&);
	outaudiofile(const char*);

	outaudiofile& operator<<(std::vector<unsigned int>&); //пишет в wav файл (data) 
	outaudiofile& operator<<(std::vector<sample>&);

	~outaudiofile();

private:

	std::ofstream audiostr;

};
