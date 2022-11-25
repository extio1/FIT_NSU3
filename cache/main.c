	#include <stdlib.h>
#include <stdio.h>
#include <intrin.h> //для __rdtsc()
#include "matrix.h" //нахождение обратной матрицы - для прогрева процессора
#include <iostream>
#include <time.h>

void print(long* arr, const int size) {
	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);
}

void direct_init(long* arr, const int size) {
	arr[size - 1] = 0;
	for (int i = 0; i < size - 1; i++) {
		arr[i] = i + 1;
	}
}

void back_init(long* arr, const int size) {
	arr[0] = size - 1;
	for (int i = size - 1; i > 0 ; i--) {
		arr[i] = i - 1;
	}
}

void warm_proc() { //работает чуть больше секунды
	Matrix warm(50);
	warm.read_from_file("mat.txt");
	inverse_matrix(warm, 3000);
}

void random_init(long* arr, const int size) {
	for (int i = 0; i < size; i++) //помечаем, что ни в какие вершины еще не зашли
		arr[i] = -1;

	int cur_pos = 0;
	unsigned long long rnd;
	//на size-1 позицию кладется индекс еще не участвующего в обходе элемента; новый индекс отличен от текущего индекса
	for (int i = 0; i < size-1; i++) { //индекс следующего элемента случайно вычисляется с помощью счетчика тактов
		do {
			rnd = __rdtsc() % size;
		} while (arr[rnd] != -1 || rnd == cur_pos);
		arr[cur_pos] = rnd;
		cur_pos = rnd;
	}
	arr[cur_pos] = 0;
}

void test(const long* arr, const int size) {
	const int k = 5; //число повторений цикла для замера среднего времени доступа к элементу массива
	unsigned long long start, end;

	warm_proc();

	for (int i = 0, k = 0; i < size; i++) { //загрузили в кэш массив
		k = arr[k];
	}

	start = __rdtsc();
	for (int i = 0, k = 0; i < size*k; i++) {
		k = arr[k];
	}
	end = __rdtsc();

	printf("Time: ");
	printf("%llu", (end - start));
}

int main() {
	int nmin = 256; // sizeof(long) * 256 = 1Kb
	int nmax = 8388608; //sizeof(long) * 8388608 = 32Mb


	long* arr = (long*)malloc(sizeof(long) * nmin);
	long* arr_dir = (long*)malloc(sizeof(long) * nmin);
	long* arr_back = (long*)malloc(sizeof(long) * nmin);
	long* arr_rand = (long*)malloc(sizeof(long) * nmin);
	direct_init(arr, nmin);
	test(arr, nmin);
	//print(arr, nmin);
	/*
	int n = nmin;
	while (n < nmax) {
		direct_init(arr, n);
		test(arr);
		back_init(arr, n);
		test(arr);
		rand_init(arr, n);
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
	*/
	free(arr_dir);
	free(arr_back);
	free(arr_rand);
}
