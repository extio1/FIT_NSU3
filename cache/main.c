#include <stdlib.h>
#include <stdio.h>
#include <intrin.h>

void direct_init(long* arr) {

}

void back_init(long* arr) {

}

void rand_init(long* arr) {

}

void test(long* arr) {
	//прогрев процессора
}

int main() {
	int nmin = 256; // sizeof(long) * 256 = 1Kb
	int nmax = 8388608; //sizeof(long) * 8388608 = 32Mb


	long* arr = (long*) malloc(sizeof(long) * nmin);
	long* arr_dir = (long*) malloc(sizeof(long) * nmin);
	long* arr_back = (long*) malloc(sizeof(long) * nmin);
	long* arr_rand = (long*) malloc(sizeof(long) * nmin);

	int n = nmin;
	while (n < nmax) {

		direct_init(arr);
		test(arr);
		back_init(arr);
		test(arr);
		rand_init(arr);
		test(arr);

		n *= 1.1;

		long* p;
		if ((p = (long*)realloc(arr, sizeof(long) * n)) != NULL) {
			arr = p;
		}
		else {
			printf("Allocation error.");
			exit(1);
		}
	}

	free(arr_dir);
	free(arr_back);
	free(arr_rand);
}
