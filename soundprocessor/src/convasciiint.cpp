
namespace {
	char arr_8_bit_to_char(const char* arr) {
		char new_char = 0;
		int exp = 1;
		for (int j = 0; j < 8; j++) {
			new_char += exp * arr[j];
			exp *= 2;
		}
		return new_char;
	}
	inline void set_zero(char* arr, int size) {
		for (int i = 0; i < size; i++)
			arr[i] = 0;
	}
}

int little_to_big_endian_byte(int num) {
	int outn;
	for (int i = 0; i < 8; i++) {
		outn = 0;
	}
	return outn;
}

int ascii_seq_to_int_le(const char* ascii, const int size) {
	int num = 0;
	for (int i = size - 1; i >= 0; i--) {
		unsigned char piece = (ascii[i] < 0) ? (ascii[i] + 256) : ascii[i];
		num <<= 8;
		num += piece;
	}
	return num;
}

void int_to_ascii_seq_le(char* ascii, const unsigned int num, const int size) { //НАПИСАТЬ ПЕРЕВОД
	char buffer[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int temp = num;
	char new_char = 0;
	int counter = 1;
	int pos = 0;
	for (int i = 0; temp >= 0; i++) {
		if (temp != 0) {
			if (i % 8 == 0 && i > 0) {
				ascii[pos++] = arr_8_bit_to_char(buffer);
				set_zero(buffer, 8);
			}
			buffer[i % 8] = temp % 2;
			temp /= 2;
			counter++;
		}
		else {
			ascii[pos] = arr_8_bit_to_char(buffer);
			break;
		}
	}
	if(pos != 3)
		for (int i = pos+1; i < 4; i++)
			ascii[i] = 0;
}
