#pragma once

int little_to_big_endian_byte(int);

int ascii_seq_to_int_le(const char*, const int);

void int_to_ascii_seq_le(char*, const unsigned int, const int);
