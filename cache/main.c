#include <stdlib.h>
#include <stdio.h>
#include <intrin.h>

int main() {
	int nmin = 256; // sizeof(long) * 256 = 1Kb
	int nmax = 8388608; //sizeof(long) * 8388608 = 32Mb

	long* arr_dir = (long*)malloc(sizeof(long) * nmin);
	long* arr_back = (long*)malloc(sizeof(long) * nmin);
	long* arr_rand = (long*)malloc(sizeof(long) * nmin);

	int n = nmin;
	while (n < nmax) {

	}

	free(arr_dir);
	free(arr_back);
	free(arr_rand);
}
