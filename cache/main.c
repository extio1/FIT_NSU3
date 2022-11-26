#include <stdlib.h>
#include <stdio.h>
//#include </usr/include/X11/Intrinsic.h> //для __rdtsc()
#include "matrix.h" //нахождение обратной матрицы - для прогрева процессора
#include <iostream>
#include <limits.h>
#include <fstream>

inline unsigned long long  get_tsc(){
	/*
	unsigned long long a;
	asm volatile ( "rdtsc\n\t"    // Пишет число тактов в EDX:EAX.
                   "shl $32, %%rdx\n\t"  // Логический сдвиг на 32 влево верхней части числа тактов
                   "or %%rdx, %0" // соединение в одно число eax и edx
                   : "=a"(a) :: "%rdx"); //a будет лежать в eax, куда rdtsc положил нижнюю часть числа тактов
	return a;*/
	unsigned long eax, edx;
    asm volatile("rdtsc\n\t": "=a" (eax), "=d" (edx));
    return (unsigned long long)eax | (unsigned long long)edx << 32;
}

void print(long* arr, const int size) {
	for (int i = 0; i < size; i++)
		printf("%ld ", arr[i]);
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

unsigned long long min_arr(const unsigned long long* arr, const int size){
	unsigned long long min = ULLONG_MAX;
	for(int i = 0; i < size; i++){
		if(arr[i] < min)
			min = arr[i];
	}
	return min;
}

void random_init(long* arr, const int size) {
	for (int i = 0; i < size; i++) //помечаем, что ни в какие вершины еще не зашли
		arr[i] = -1;

	int cur_pos = 0;
	srand(time(NULL));
	unsigned long long rnd;
	//на size-1 позицию кладется индекс еще не участвующего в обходе элемента; новый индекс отличен от текущего индекса
	for (int i = 0; i < size-1; i++) { //индекс следующего элемента случайно вычисляется с помощью счетчика тактов
		do {
			rnd = rand() % size;
		} while (arr[rnd] != -1 || rnd == cur_pos);

		arr[cur_pos] = rnd;
		cur_pos = rnd;
	}
	arr[cur_pos] = 0;
}

int test(const long* arr, const int size) {
	const int k = 5; //число повторений цикла для замера среднего времени доступа к элементу массива
	const int precision = 5; //количество повторений теста, для более точных замеров времени
	unsigned long long times[k];
	unsigned long long start = 0, end = 0;

	warm_proc();
	int j = 0;
	for (int i = 0, j = 0; i < size; i++) { //загрузили в кэш массив
		j = arr[j];
	}
	if (j != 0){
		printf("%d", j);
	}

	for(int m = 0; m < precision; m++){
		int i = 0;
		int j = -1;

		start = get_tsc();
		for (j = 0; i < size*k; i++) {
			j = arr[j];
		}
		end = get_tsc();

		if (j != 0){
			printf("Ok ");
		}

		times[m] = end - start;
	}

	return min_arr(times, precision) / (size * k); //всего обращений в память n*size, 
									               //время за которое они произошли - это end - start (время в тактах процессора)
}

int main() {
	int nmin = 256; // sizeof(long) * 256 = 1Kb
	int nmax = 8388608; //sizeof(long) * 8388608 = 32Mb

	std::ofstream outcsv;
	outcsv.open("cacheout.csv");
	outcsv << "Size;" << "Direct;" << "Back;" << "Random;\n";

	long* arr = (long*)malloc(sizeof(long) * nmin);

	int n = nmin;
	while (n < nmax) {
		int temp;

		//printf("%d b:\n-------------------------------\n", n * 4);
		outcsv << n*4;
		outcsv << ';';

		direct_init(arr, n);
		//printf("Direct: %d \n", test(arr, n));
		outcsv << test(arr, n);
		outcsv << ';';

		back_init(arr, n);
		//printf("Back: %d \n", test(arr, n));
		outcsv << test(arr, n);
		outcsv << ';';

		random_init(arr, n);
		//printf("Random: %d \n", test(arr, n));
		outcsv << test(arr, n);
		outcsv << ';';

		//printf("-------------------------------\n");
		outcsv << '\n';

		n *= 1.2;

		long* p;
		if ((p = (long*)realloc(arr, sizeof(long) * n)) != NULL) {
			arr = p;
		}
		else {
			printf("Allocation error.");
			exit(1);
		}
	}

	free(arr);
	outcsv.close();
}
