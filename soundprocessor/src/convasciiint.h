#pragma once
#include<vector>

int little_to_big_endian_byte(int);
int ascii_seq_to_int_le(const char*, const int);
int ascii_seq_to_int(const char*, const int);
int ascii_seq_to_int(std::vector<char>&, const int);
void int_to_ascii_seq_le(char*, const unsigned int, const int);
void int_to_ascii_seq(std::vector<char>&, const unsigned int, const int);
